// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"
//#include "MPU6050.h" // not necessary if using MotionApps include file

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
//AD0 low = 0x68 //(default for SparkFun breakout and InvenSense evaluation board)
//AD0 high = 0x69
//MPU6050 mpu;
MPU6050 mpu(0x69); // <-- use for AD0 high

//#define OUTPUT_READABLE_EULER

#define OUTPUT_READABLE_YAWPITCHROLL

char val;



#define INTERRUPT_PIN 2  // use pin 2 on Arduino Uno & most boards

bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, 0x00, '\r', '\n' };


volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
  mpuInterrupt = true;
}



int LED = 12;
int lowKey = 2250;
int highKey = 1050;
int lowWord = 600;
int highWord = 950;
void setup()
{
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif


  Serial.begin(9600);
  while (!Serial);
  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);
  while (Serial.available() && Serial.read()); // empty buffer
  while (!Serial.available());                 // wait for data
  while (Serial.available() && Serial.read()); // empty buffer again
  devStatus = mpu.dmpInitialize();
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip
  if (devStatus == 0) {
    mpu.setDMPEnabled(true);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();
    dmpReady = true;

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  }
  //pinMode(LED, OUTPUT);
}

void loop()
{

  if (Serial.available())
  {
    val = Serial.read();
    /***************************************************/
    if (val == 'W' || val == 'w')             //FORWARD
    {
      for (int i = 1; i <= 4; i++) {        //KEY
        digitalWrite(LED, HIGH);
        delayMicroseconds( highKey);
        digitalWrite(LED, LOW);
        delayMicroseconds(lowKey);
      }                                     // END KEY
      for (int i = 1; i <= 10; i++) {       //WORD
        digitalWrite(LED, HIGH);
        delayMicroseconds(highWord);
        digitalWrite(LED, LOW);
        delayMicroseconds(lowWord);
      }                                     // END WORD
    }                                        // END FORWARD
    /**********************************************   */
    if ( val == 'S' || val == 's')            // BACKWARD
    {
      for (int i = 1; i <= 4; i++) {          //KEY
        digitalWrite(LED, HIGH);
        delayMicroseconds(highKey);
        digitalWrite(LED, LOW);
        delayMicroseconds(lowKey);
      }                                       //END KEY
      for (int i = 1; i <= 40; i++) {         // WORD
        digitalWrite(LED, HIGH);
        delayMicroseconds(highWord);
        digitalWrite(LED, LOW);
        delayMicroseconds(lowWord);
      }                                       // END WORD
    }                                         //END BACKWARD
    /************************************************/
    if (val == 'A' || val == 'a') {           //LEFT
      for (int i = 1; i <= 4; i++) {         //KEY
        digitalWrite(LED, HIGH);
        delayMicroseconds(highKey);
        digitalWrite(LED, LOW);
        delayMicroseconds(lowKey);
      }                                       //END KEY
      for (int i = 1; i <= 58; i++) {         // WORD
        digitalWrite(LED, HIGH);
        delayMicroseconds(highWord);
        digitalWrite(LED, LOW);
        delayMicroseconds(lowWord);
      }                                       //END WORD
    }                                         //END LEFT
    /*******************************************************/
    if (val == 'd' || val == 'D') {           //RIGTH
      for (int i = 1; i <= 4; i++) {         //KEY
        digitalWrite(LED, HIGH);
        delayMicroseconds(highKey);
        digitalWrite(LED, LOW);
        delayMicroseconds(lowKey);
      }                                       //END KEY
      for (int i = 1; i <= 64; i++) {         //WORD
        digitalWrite(LED, HIGH);
        delayMicroseconds(highWord);
        digitalWrite(LED, LOW);
        delayMicroseconds(lowWord);
      }                                       //END WORD
    }                                         //END RIGTH
    /*****************************************************/
    if (val == 'g') {                        //BACKWARD&LEFT
      for (int i = 1; i <= 4; i++) {       //KEY
        digitalWrite(LED, HIGH);
        delayMicroseconds(highKey);
        digitalWrite(LED, LOW);
        delayMicroseconds(lowKey);
      }                                    //END KEY
      for (int i = 1; i <= 52; i++) {      //WORD
        digitalWrite(LED, HIGH);
        delayMicroseconds(highWord);
        digitalWrite(LED, LOW);
        delayMicroseconds(lowWord);
      }                                   //END WORD
    }                                    //END BACKWARD&LEFT
    /*********************************************************/
    if (val == 'h') {                      //BACKWARD&RIGTH
      for (int i = 1; i <= 4; i++) {     //KEY
        digitalWrite(LED, HIGH);
        delayMicroseconds(highKey);
        digitalWrite(LED, LOW);
        delayMicroseconds(lowKey);
      }                                  //END KEY
      for (int i = 1; i <= 46; i++) {    //WORD
        digitalWrite(LED, HIGH);
        delayMicroseconds(highWord);
        digitalWrite(LED, LOW);
        delayMicroseconds(lowWord);
      }                                  //END WORD
    }                                    //END BACKWARD&RIGTH
    /************************************************************/
    if (val == 'j') {                      //FORWARD&RIGTH
      for (int i = 1; i <= 4; i++) {     //KEY
        digitalWrite(LED, HIGH);
        delayMicroseconds(highKey);
        digitalWrite(LED, LOW);
        delayMicroseconds(lowKey);
      }                                  //END KEY
      for (int i = 1; i <= 34; i++) {    //WORD
        digitalWrite(LED, HIGH);
        delayMicroseconds(highWord);
        digitalWrite(LED, LOW);
        delayMicroseconds(lowWord);
      }                                  //END WORD
    }                                    //END FORWARD&RIGTH
    /***************************************************************/
    if (val == 'k') {                      //FORWARD&LEFT
      for (int i = 1; i <= 4; i++) {     //KEY
        digitalWrite(LED, HIGH);
        delayMicroseconds(highKey);
        digitalWrite(LED, LOW);
        delayMicroseconds(lowKey);
      }                                  //END KEY
      for (int i = 1; i <= 28; i++) {    //WORD
        digitalWrite(LED, HIGH);
        delayMicroseconds(highWord);
        digitalWrite(LED, LOW);
        delayMicroseconds(lowWord);
      }                                  //END WORD
    }                                   //END FORWARD&LEFT
    /***************************************************************/
  }
  /* if (!dmpReady) return;
    while (!mpuInterrupt && fifoCount < packetSize) {
     // other program behavior stuff here
     // .
     // .
     // .
     // if you are really paranoid you can frequently test in between other
     // stuff to see if mpuInterrupt is true, and if so, "break;" from the
     // while() loop to immediately process the MPU data
     // .
     // .
     // .
    }*/
  /* mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();*/
  fifoCount = mpu.getFIFOCount();
  /*if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    // reset so we can continue cleanly
    mpu.resetFIFO();
    Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    }*/// else if (mpuIntStatus & 0x02) {
  // wait for correct available data length, should be a VERY short wait
  while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

  // read a packet from FIFO
  mpu.getFIFOBytes(fifoBuffer, packetSize);

  // track FIFO count here in case there is > 1 packet available
  // (this lets us immediately read more without waiting for an interrupt)
  fifoCount -= packetSize;
  mpu.dmpGetQuaternion(&q, fifoBuffer);
  mpu.dmpGetAccel(&aa, fifoBuffer);
  mpu.dmpGetGravity(&gravity, &q);
  mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
  mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
  digitalWrite(0 , aaWorld.x / 16000);
  digitalWrite(0 , aaWorld.y / 16000);
  Serial.print(aaWorld.x / 16000);
  Serial.print(aaWorld.y / 16000);
}
//}








