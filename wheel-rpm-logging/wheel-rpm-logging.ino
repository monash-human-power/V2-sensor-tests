/**
 * Wheel speed rpm logging using the V2 DAS
 */

// Commas or spaces?
#define SEPARATOR ","
// #define SEPARATOR " "

// Pins
#define REED_SWITCH 2
#define LED_EXTERNAL 13

#define MIN_TIME 40000 // Minimum rotation time  (us) for debouncing purposes
#define BAUD_RATE 115200
#define RPM_CONVERSION_FACTOR 60*1000*1000 // 60 seconds in a minute, 1000 ms in a s, 1000 us in a ms
volatile unsigned int rotationFlag = false;
volatile uint32_t curTime = 0;
volatile uint32_t prevTime = 0;
volatile uint32_t lockoutTime = 0; // For debouncing
volatile unsigned long rotations = 0;

void setup() {
  // Hardware
  pinMode(REED_SWITCH, INPUT_PULLUP);
  pinMode(LED_EXTERNAL, OUTPUT);
  digitalWrite(LED_EXTERNAL, HIGH); // Turn the led on until first rotation to show readiness
  attachInterrupt(REED_SWITCH, reedInterrupt, CHANGE);

  // Serial
  Serial.begin(BAUD_RATE);
  while(!Serial) {
    // Let the user know the computer is not connected correctly
    digitalWrite(LED_EXTERNAL, LOW);
    delay(100);
    digitalWrite(LED_EXTERNAL, HIGH);
    delay(100);
  }
  // Serial.println(F("MHP Wheel speed logging. Compiled" __TIME__ "," __DATE__));
  Serial.println(F("Time" SEPARATOR "Rotation_Number" SEPARATOR "Rotation_Time" SEPARATOR "RPM"));
}

void loop() {
  // Do the time consuming stuff outside the ISR
  if(rotationFlag) {
    // Disable interrupts whilst reading to avoid race conditions.
    noInterrupts();
    unsigned long rotationTime = curTime - prevTime;
    unsigned int rpm = RPM_CONVERSION_FACTOR / rotationTime;
    unsigned long rotationsCopy = rotations; // To avoid race conditions
    unsigned long curTimeCopy = curTime;
    interrupts();

    Serial.print(curTimeCopy);
    Serial.write(SEPARATOR);
    Serial.print(rotationsCopy);
    Serial.write(SEPARATOR);
    Serial.print(rotationTime);
    Serial.write(SEPARATOR);
    Serial.println(rpm);
    rotationFlag = false;
  }
  if(Serial.available() && Serial.read() == 'r') {
    // Reset if 'r' is sent
    Serial.println(F("'r' received, so resetting..."));
    Serial.flush();
    delay(200);
    SCB_AIRCR = 0x05FA0004; // https://forum.pjrc.com/threads/30567-Hardware-reset-on-Teensy-LC
  }
}

/**
 * Interrupt for the reed switch being triggered.
 */
void reedInterrupt() {
  uint32_t now = micros();
  if(digitalReadFast(REED_SWITCH) && lockoutTime >= MIN_TIME) {
    // Switch opened and no event interrupts for the last little while
    // Assume this is a genuine wheel rotation and not switch bounce.
    digitalWrite(LED_EXTERNAL, rotations & 0x1); // Toggle the led (lsb of rotations toggles each time).
    rotations++;
    prevTime = curTime;
    curTime = now;
    rotationFlag = true;
  }
  // Lockout for switch opened or switch closed (helps with debouncing at slow speeds)
  lockoutTime = now;
}

