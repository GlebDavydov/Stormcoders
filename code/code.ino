#include <Wire.h>
#include "gyro_accel.h"
// Defining constants
#define dt 100                      // time diffrence in milli seconds
#define rad2degree 57.3              // Radian to degree conversion
#define Filter_gain 0.95             // e.g.  angle = angle_gyro*Filter_gain + angle_accel*(1-Filter_gain)

char val;

unsigned long t=0; // Time Variables
float angle_x_gyro=0,angle_y_gyro=0,angle_z_gyro=0,angle_x_accel=0,angle_y_accel=0,angle_z_accel=0,angle_x=0,angle_y=0,angle_z=0;

int LED = 12;
int lowKey = 2250;  
int highKey = 1050;
int lowWord = 600;
int highWord = 950;
void setup()
{
Serial.begin(9600);
  MPU6050_ResetWake();
  MPU6050_SetGains(0,0);// Setting the lows scale
  MPU6050_SetDLPF(0); // Setting the DLPF to inf Bandwidth for calibration
  MPU6050_OffsetCal();
  MPU6050_SetDLPF(3); // Setting the DLPF to 44 GHZ
pinMode(LED, OUTPUT);
}

void loop()
{
if (Serial.available())
{
val = Serial.read(); 
/***************************************************/
if (val == 'W' || val == 'w')             //FORWARD
{
    for(int i = 1; i <= 4; i++){          //KEY
        digitalWrite(LED, HIGH);
        delayMicroseconds( highKey);
        digitalWrite(LED, LOW);
        delayMicroseconds(lowKey);
    }                                     // END KEY
    for(int i = 1; i <=10; i++){          //WORD
      digitalWrite(LED, HIGH);
      delayMicroseconds(highWord);
      digitalWrite(LED, LOW);
      delayMicroseconds(lowWord);
    }                                     // END WORD
}                                         // END FORWARD
/**********************************************   */
if ( val == 'S'|| val == 's')             // BACKWARD
{ 
  for(int i = 1; i <= 4; i++){            //KEY
    digitalWrite(LED, HIGH);
    delayMicroseconds(highKey);
    digitalWrite(LED, LOW);
    delayMicroseconds(lowKey);
  }                                       //END KEY
  for(int i = 1; i <= 40; i++){           // WORD
    digitalWrite(LED, HIGH);
    delayMicroseconds(highWord);
    digitalWrite(LED, LOW);
    delayMicroseconds(lowWord);
  }                                       // END WORD
}                                         //END BACKWARD
/************************************************/
if (val == 'A' || val == 'a'){            //LEFT
   for(int i = 1; i <= 4; i++){           //KEY
    digitalWrite(LED, HIGH);
    delayMicroseconds(highKey);
    digitalWrite(LED, LOW);
    delayMicroseconds(lowKey);
  }                                       //END KEY
  for(int i = 1; i <=58; i++){            // WORD
    digitalWrite(LED, HIGH);
    delayMicroseconds(highWord);
    digitalWrite(LED, LOW);
    delayMicroseconds(lowWord);
  }                                       //END WORD
}                                         //END LEFT
/*******************************************************/
if (val == 'd' || val == 'D'){            //RIGTH
   for(int i = 1; i <= 4; i++){           //KEY
    digitalWrite(LED, HIGH);
    delayMicroseconds(highKey);
    digitalWrite(LED, LOW);
    delayMicroseconds(lowKey);
  }                                       //END KEY
  for(int i = 1; i <= 64; i++){           //WORD
    digitalWrite(LED, HIGH);
    delayMicroseconds(highWord);
    digitalWrite(LED, LOW);
    delayMicroseconds(lowWord);
  }                                       //END WORD
}                                         //END RIGTH
/*****************************************************/
 if(val == 'g'){                          //BACKWARD&LEFT
     for(int i = 1; i <= 4; i++){         //KEY
      digitalWrite(LED, HIGH);
      delayMicroseconds(highKey);
      digitalWrite(LED, LOW);
      delayMicroseconds(lowKey);
    }                                    //END KEY
    for(int i = 1; i <= 52; i++){        //WORD
      digitalWrite(LED, HIGH);
      delayMicroseconds(highWord);
      digitalWrite(LED, LOW);
      delayMicroseconds(lowWord);
    }                                   //END WORD
  }                                     //END BACKWARD&LEFT
/*********************************************************/
 if(val == 'h'){                        //BACKWARD&RIGTH
     for(int i = 1; i <= 4; i++){       //KEY
      digitalWrite(LED, HIGH);
      delayMicroseconds(highKey);
      digitalWrite(LED, LOW);
      delayMicroseconds(lowKey);
    }                                  //END KEY
    for(int i = 1; i <= 46; i++){      //WORD
      digitalWrite(LED, HIGH);
      delayMicroseconds(highWord);
      digitalWrite(LED, LOW);
      delayMicroseconds(lowWord);
    }                                  //END WORD
 }                                     //END BACKWARD&RIGTH
 /************************************************************/
  if(val == 'j'){                        //FORWARD&RIGTH
     for(int i = 1; i <= 4; i++){       //KEY
      digitalWrite(LED, HIGH);
      delayMicroseconds(highKey);
      digitalWrite(LED, LOW);
      delayMicroseconds(lowKey);
    }                                  //END KEY
    for(int i = 1; i <= 34; i++){      //WORD
      digitalWrite(LED, HIGH);
      delayMicroseconds(highWord);
      digitalWrite(LED, LOW);
      delayMicroseconds(lowWord);
    }                                  //END WORD
 }                                     //END FORWARD&RIGTH
 /***************************************************************/
   if(val == 'k'){                        //FORWARD&LEFT
     for(int i = 1; i <= 4; i++){       //KEY
      digitalWrite(LED, HIGH);
      delayMicroseconds(highKey);
      digitalWrite(LED, LOW);
      delayMicroseconds(lowKey);
    }                                  //END KEY
    for(int i = 1; i <= 28; i++){      //WORD
      digitalWrite(LED, HIGH);
      delayMicroseconds(highWord);
      digitalWrite(LED, LOW);
      delayMicroseconds(lowWord);
    }                                  //END WORD
 }                                     //END FORWARD&LEFT
 /***************************************************************/
}
MPU6050_ReadData();
 
  angle_x_gyro = (gyro_x_scalled*((float)dt/1000)+angle_x);
  angle_y_gyro = (gyro_y_scalled*((float)dt/1000)+angle_y);
  angle_z_gyro = (gyro_z_scalled*((float)dt/1000)+angle_z);

  angle_z_accel = atan(accel_z_scalled/(sqrt(accel_y_scalled*accel_y_scalled+accel_x_scalled*accel_x_scalled)))*(float)rad2degree;
  angle_y_accel = -atan(accel_x_scalled/(sqrt(accel_y_scalled*accel_y_scalled+accel_z_scalled*accel_z_scalled)))*(float)rad2degree;
  angle_x_accel = atan(accel_y_scalled/(sqrt(accel_x_scalled*accel_x_scalled+accel_z_scalled*accel_z_scalled)))*(float)rad2degree;

  angle_x = Filter_gain*angle_x_gyro+(1-Filter_gain)*angle_x_accel;
  angle_y = Filter_gain*angle_y_gyro+(1-Filter_gain)*angle_y_accel;
  angle_z = Filter_gain*angle_z_gyro+(1-Filter_gain)*angle_z_accel;
}
