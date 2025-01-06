/**
 * Wheel speed rpm logging for Arduino Uno R3
 */

// Commas or spaces?
#define SEPARATOR "," // Change to " " if spaces are preferred

// Pins
#define REED_SWITCH 2 // Interrupt pin for Arduino Uno
#define LED_EXTERNAL 13

#define MIN_TIME 20000 // Minimum rotation time (us) for debouncing
#define BAUD_RATE 115200
#define RPM_CONVERSION_FACTOR 60 // 60 seconds in a minute
#define AV_CONVERSION_FACTOR TWO_PI
#define PRINT_DECIMALS 15

volatile bool rotationFlag = false;
volatile uint32_t curTime = 0;
volatile uint32_t prevTime = 0;
volatile unsigned long rotations = 0;
double prevAV = 0;

void setup() {
  // Hardware setup
  pinMode(REED_SWITCH, INPUT_PULLUP); // Internal pull-up resistor
  pinMode(LED_EXTERNAL, OUTPUT);
  digitalWrite(LED_EXTERNAL, HIGH); // LED on to indicate readiness

  // Serial setup
  Serial.begin(BAUD_RATE);
  while (!Serial) {
    // Blink LED if serial connection is not ready
    digitalWrite(LED_EXTERNAL, LOW);
    delay(100);
    digitalWrite(LED_EXTERNAL, HIGH);
    delay(100);
  }
  Serial.println("Time_us" SEPARATOR "Rotation_Number" SEPARATOR "Rotation_Time_us" SEPARATOR "Angular_V_rad_s" SEPARATOR "Angular_A_rad_s2" SEPARATOR "RPM");

  // Enable the interrupt for the reed switch
  attachInterrupt(digitalPinToInterrupt(REED_SWITCH), reedInterrupt, FALLING);
}

void loop() {
  if (rotationFlag) {
    // Disable interrupts to avoid race conditions
    noInterrupts();
    unsigned long rotationTime = curTime - prevTime;
    unsigned long rotationsCopy = rotations;
    unsigned long curTimeCopy = curTime;
    interrupts();

    double rotationTimeSeconds = (double)rotationTime / 1e6;
    double rpm = RPM_CONVERSION_FACTOR / rotationTimeSeconds;
    double angularV = AV_CONVERSION_FACTOR / rotationTimeSeconds;
    double angularA = (angularV - prevAV) / rotationTimeSeconds;
    prevAV = angularV;

    // Print data
    Serial.print(curTimeCopy);
    Serial.write(SEPARATOR);
    Serial.print(rotationsCopy);
    Serial.write(SEPARATOR);
    Serial.print(rotationTime);
    Serial.write(SEPARATOR);
    Serial.print(angularV, PRINT_DECIMALS);
    Serial.write(SEPARATOR);
    Serial.print(angularA, PRINT_DECIMALS);
    Serial.write(SEPARATOR);
    Serial.println(rpm, PRINT_DECIMALS);

    rotationFlag = false;
  }

  if (Serial.available() && Serial.read() == 'r') {
    // Reset logic: restart Arduino via watchdog timer
    Serial.flush();
    delay(200);
    wdt_enable(WDTO_15MS); // Enable the watchdog timer for a 15ms timeout
    while (1) {} // Trigger reset by keeping the watchdog active
  }
}

/**
 * Interrupt Service Routine for the reed switch
 */
void reedInterrupt() {
  uint32_t now = micros();
  if (now - curTime >= MIN_TIME) {
    // Debouncing check: genuine rotation
    digitalWrite(LED_EXTERNAL, rotations & 0x1); // Toggle LED
    rotations++;
    prevTime = curTime;
    curTime = now;
    rotationFlag = true;
  }
}
