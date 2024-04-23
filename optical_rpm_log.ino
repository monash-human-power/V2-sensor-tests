#define SEPARATOR ","

//Pins
#define TCRT_DIG 2
#define TCRT_ANLG A0

//
volatile int digital_val;
int counter = 0;
volatile unsigned prevRPM = 0;

#define MIN_TIME 50000
#define BAUD_RATE 115200
#define RPM_CONVERSION_FACTOR 60
#define AV_CONVERSION_FACTOR TWO_PI
#define PRINT_DECIMALS 15

volatile unsigned int rotationFlag = false;
volatile uint32_t curTime = 0;
volatile uint32_t prevTime = 0;
volatile unsigned long rotations = 0;
double prevAV = 0;

void irInterrupt(){
  uint32_t now = micros();
  if(now - curTime >= MIN_TIME) {
    // Switch closed and no event interrupts for the last little while
    // Assume this is a genuine wheel rotation and not switch bounce.
    rotations++;
    prevTime = curTime;
    curTime = now;
    rotationFlag = true;
  }
}

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(TCRT_DIG, INPUT_PULLUP);
  pinMode(TCRT_ANLG, INPUT);
  // Serial.println(F("MHP Wheel speed logging. Compiled" __TIME__ "," __DATE__));
  Serial.println("Time_us" SEPARATOR "Rotation_Number" SEPARATOR "Rotation_Time_us" SEPARATOR "Angular_V_rad_s" SEPARATOR "Angular_A_rad_s2" SEPARATOR "RPM");

  // Enable the switch
  attachInterrupt(digitalPinToInterrupt(TCRT_DIG),irInterrupt, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
//  digital_val2 = digitalRead(TCRT_DIG);
   if(rotationFlag) {
    // Disable interrupts whilst reading to avoid race conditions.
    
    
    noInterrupts();
    unsigned long rotationTime = curTime - prevTime;
    unsigned long rotationsCopy = rotations; // To avoid race conditions
    unsigned long curTimeCopy = curTime;
    interrupts();

    double rotationTimeSeconds = (double)rotationTime / 1e6;
    double rpm = RPM_CONVERSION_FACTOR / rotationTimeSeconds; // rpm if the differnce between 2 values is above 300 ignore
    double angularV = AV_CONVERSION_FACTOR / rotationTimeSeconds;
    double angularA = (angularV - prevAV) / rotationTimeSeconds;
    prevAV = angularV;

    
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
    prevRPM = rpm; //change
  }
}
// when speed up okay, there isn't a lot of chnage; but when the speed decreases very fast there are random values
//schmitt trigger
