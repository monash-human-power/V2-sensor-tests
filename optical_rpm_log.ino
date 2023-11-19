float REV = 0;
int RPM_VALUE;
int PREVIOUS = 0;
int TIME;

void INTERRUPT()
{
  REV++;
}

void setup()
{
  Serial.begin(9600);
  attachInterrupt(3, INTERRUPT, RISING);
}

void loop()
{
  delay(1000);
  detachInterrupt(0);      
  TIME = millis() - PREVIOUS;          
  RPM_VALUE = (REV/TIME) * 60000;       
  PREVIOUS = millis();                  
  REV = 0;
  Serial.println(RPM_VALUE);
  attachInterrupt(1, INTERRUPT, RISING); 
}
/**
 * Wheel speed rpm logging using the V2 DAS
   changed few things in orginal wheel-rpm-logging code
 */
//
//// Commas or spaces?
//#define SEPARATOR ","
//// #define SEPARATOR " "
//
//// Pins
//#define REED_SWITCH 3
//#define LED_EXTERNAL 13
//
//#define MIN_TIME 20000 // Minimum rotation time  (us) for debouncing purposes
//#define BAUD_RATE 115200
//#define RPM_CONVERSION_FACTOR 60 // 60 seconds in a minute
//#define AV_CONVERSION_FACTOR TWO_PI
//#define PRINT_DECIMALS 15
//
//volatile unsigned int rotationFlag = false; 
//volatile uint32_t curTime = 0;
//volatile uint32_t prevTime = 0;
//volatile unsigned long rotations = 0;
//double prevAV = 0;
//
//#define RESET()
//
//void setup() {
//  // Hardware
//  pinMode(REED_SWITCH, INPUT);

//
//  // Serial
//  Serial.begin(BAUD_RATE);
//  while(!Serial) {
////    // Let the user know the computer is not connected correctly
////    digitalWrite(LED_EXTERNAL, LOW);
////    delay(100);
////    digitalWrite(LED_EXTERNAL, HIGH);
////    delay(100);
////  }
//  // Serial.println(F("MHP Wheel speed logging. Compiled" __TIME__ "," __DATE__));
//  Serial.println("Time_us" SEPARATOR "Rotation_Number" SEPARATOR "Rotation_Time_us" SEPARATOR "Angular_V_rad_s" SEPARATOR "Angular_A_rad_s2" SEPARATOR "RPM");
//
//  // Enable the switch
//  attachInterrupt(REED_SWITCH, reedInterrupt, RISING);
//}
//
//void loop() {
//  // Do the time consuming stuff outside the ISR
//  if(rotationFlag) {
//    // Disable interrupts whilst reading to avoid race conditions.
//    noInterrupts();
//    unsigned long rotationTime = curTime - prevTime;
//    unsigned long rotationsCopy = rotations; // To avoid race conditions
//    unsigned long curTimeCopy = curTime;
//    interrupts();
//
//    double rotationTimeSeconds = (double)rotationTime / 1e6;
//    double rpm = RPM_CONVERSION_FACTOR / rotationTimeSeconds;
//    double angularV = AV_CONVERSION_FACTOR / rotationTimeSeconds;
//    double angularA = (angularV - prevAV) / rotationTimeSeconds;
//    prevAV = angularV;
//
//    Serial.print(curTimeCopy);
//    Serial.write(SEPARATOR);
//    Serial.print(rotationsCopy);
//    Serial.write(SEPARATOR);
//    Serial.print(rotationTime);
//    Serial.write(SEPARATOR);
//    Serial.print(angularV, PRINT_DECIMALS);
//    Serial.write(SEPARATOR);
//    Serial.print(angularA, PRINT_DECIMALS);
//    Serial.write(SEPARATOR);
//    Serial.println(rpm, PRINT_DECIMALS);
//    rotationFlag = false;
//  }
//
//  if(Serial.available() && Serial.read() == 'r') {
//    // Reset if 'r' is sent
//    // Serial.println(F("'r' received, so resetting...")); // Don't pollute the new file with this message
//    Serial.flush();  ///???????
//    delay(200);
//    RESET();
//  }
//}
//
///**
// * Interrupt for the reed switch being triggered.
// */
//void reedInterrupt() {
//  uint32_t now = micros();
//  if(now - curTime >= MIN_TIME) {
//    // Switch closed and no event interrupts for the last little while
//    // Assume this is a genuine wheel rotation and not switch bounce.
////    digitalWrite(LED_EXTERNAL, rotations & 0x1); // Toggle the led (lsb of rotations toggles each time). <-- ???
//    rotations++;
//    prevTime = curTime;
//    curTime = now;
//    rotationFlag = true;
//  }
//}