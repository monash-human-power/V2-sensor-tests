// Pin Values
static const int REED_SWITCH_PIN = 2; // Other pin to GND


// Set up reed switch
volatile unsigned long PREV_REED_SWITCH_TIME = 0;
volatile unsigned long REED_SWITCH_COUNTER = 0;
volatile unsigned long PREV_REED_SWITCH_COUNT = 0;
volatile float VELOCITY = 0, DISTANCE = 0;
IntervalTimer reedSwitchTimer;

// 700C Rims + 33mm tyre
const float WHEEL_DIAMETER = 0.622 + (0.033 * 2);
const float WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * PI;

void setup() {
  // Set up Reed Switch
  pinMode(REED_SWITCH_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(REED_SWITCH_PIN), reedSwitchInterruptHandler, FALLING); // interrrupt 1 is data ready
  // Check if stopped every 3 seconds
  reedSwitchTimer.begin(reedSwitchChecker, 3 * 1000000);
}

void loop() {
  Serial.println("Velocity: " + String(VELOCITY, 4));
  Serial.println("Distance: " + String(DISTANCE, 4));
  Serial.println();
  delay(100);
}

void reedSwitchInterruptHandler() {
  // Get start time
  if(PREV_REED_SWITCH_TIME == 0) {
    PREV_REED_SWITCH_TIME = millis();
    VELOCITY = 0;
    return;
  }
  unsigned long current_time = millis();
  unsigned long total_time = current_time - PREV_REED_SWITCH_TIME;
  // 50ms means we have a maximum velocity of 180km/h with a wheel diameter of 0.8
  if(total_time <= 50) {
    return;
  }

  // Count how many times wheel rotates
  REED_SWITCH_COUNTER = REED_SWITCH_COUNTER + 1;

  // Calculate velocity and distance
  VELOCITY = (1/(float)total_time) * PI * WHEEL_DIAMETER * 3600;
  DISTANCE = REED_SWITCH_COUNTER * WHEEL_CIRCUMFERENCE;
  PREV_REED_SWITCH_TIME = current_time;
}

// Check if the bike has stopped
void reedSwitchChecker() {
  if(PREV_REED_SWITCH_COUNT != REED_SWITCH_COUNTER) {
    PREV_REED_SWITCH_COUNT = REED_SWITCH_COUNTER;
  } else {
    // Stopped!
    noInterrupts();
    PREV_REED_SWITCH_TIME = 0;
    VELOCITY = 0;
    interrupts();
  }
}
