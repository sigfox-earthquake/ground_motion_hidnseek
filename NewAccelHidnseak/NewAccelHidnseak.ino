/**
 * Copyright (c) 2014 panStamp <contact@panstamp.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * any later version.
 * 
 * panStamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with panStamp; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 
 * USA
 * 
 * Author: Daniel Berenguer
 * Creation date: 08/06/2014
 */
 
/**
 * Basic sketch usinglow-power modes and interrupts witha MMA8652FC 3-Axis
 * accelerometer.
 */
 #include "mma8652_regs.h"
#include "HardwareSerial.h"
#include "Wire.h"
#include "mma8652.h"

//#include "HidnSeek.h"

// Accelerometer object. Interruptable pin = internal ACC_INT pin
#define ACC_INT  11 // Accelerometer interrupt pin
//#define ACC_INT  5 // Accelerometer interrupt pin possibly?
#define ACC_POWER_PIN 9 // Power pin from the host
//#define bluLEDpin 6     // PD6 Piezzo Output
#define LED 7     // PD7 Red LED Status
MMA8652 accel = MMA8652(ACC_INT); 

// Used to read statuses and source registers
uint8_t status, intSource;
int x = 0;
int y = 0;
int z = 0;
int last_x = 0;
int last_y = 0;
int last_z = 0;
int on = -1;

/**
 * accEvent
 *
 * Custom ISR. Will be called whenever the accelerometer generates an interupt
 */
void accEvent(void)
{
//  for (int i = 0; i < 1000; i++){
    Serial.println("Calling accEvent");
    //}
//  delay(100000);
  digitalWrite(LED, !digitalRead(LED));
//  panstamp.wakeUp();
}

/**
 * setup
 */
void setup()
{
//  on = 0;
  Serial.begin(9600);
  Serial.println("Starting...");

  pinMode(LED, OUTPUT);

  // Turn ON accelerometer
  pinMode(ACC_POWER_PIN, OUTPUT);
  digitalWrite(ACC_POWER_PIN, HIGH);
  delay(100);

  // Init accelerometer
  accel.init();
  delay(1);
  
  // Enable single-tap detection interruption
  accel.enableTapInt(0x10);
//  accel.enableTapInt(0);
  delay(1);
//  // Enable Portrait/Landscape orientation interrupt
//  accel.enablePlInt();
//  delay(1);
//  // Enable Free-Fall detection interrupt
////  accel.enableFreeFallInt(0x30);
//  accel.enableFreeFallInt(3);
//  delay(1);

  // Declare custom ISR
  accel.attachInterrupt(accEvent);
}

/**
 * loop
 */
void loop()
{ 
  // Go to sleep
  digitalWrite(LED, LOW);
  accel.sleep();    // Accelerometer in sleep mode

//  panstamp.sleep(); // panStamp in sleep mode
//  digitalWrite(LED, HIGH);

//Serial.println(accel.read(SMOD_LOW_POWER));
//Serial.println(accel.read(CTRL_REG5), HEX);
//Serial.println(accel.read(CTRL_REG1), HEX);
  /**
   * We could be polling for an ACC event but we prefer to be interrupted instead
   * If you want to display all the above Serial.prints correctly then comment
   * panstamp.sleep() out and uncomment the following line
   */
//   Serial.println((String)"double tap:        " + enableDoubleTapInt(50));
//   if (accel.eventAvailable()) {}//Serial.println(accel.eventAvailable());}
  
  // Read source of interrupt
//    Serial.println(intSource, HEX);
  intSource = accel.readIntSource();
  delay(10);

  if(SRC_PULSE_MASK || (on >= 0))
  {
    status = accel.readPulseSource();
    if (status == 0xC0|| (on >= 0)){
//if (on == 0)
//  digitalWrite(accel.read(CTRL_REG1));//ASLP_RATE1, 
  digitalWrite(LED, HIGH);
//Serial.println(accel.read(SYSMOD_SLEEP), HEX);
//delay(10);
  // Read XYZ data. Available from accel.axis
  accel.readXYZ();
//
// last_x = x;
// last_y = y;
// last_z = z;

 x = accel.axis.x;
 y = accel.axis.y;
 z = accel.axis.z;
// if (abs(last_x - x) > 50)
//  Serial.println("detected x");
// else if (abs(last_y - y) > 50)
//  Serial.println("detected y");
// else if (abs(last_z - z) > 50)
//  Serial.println("detected z");
// else
//  accel.sleep();
//if ((abs(last_x - x) > 50) || (abs(last_y - y) > 50) || (abs(last_z - z) > 50) || (on >= 0)){
  Serial.print(",");//X axis : ");
  Serial.print(x);
  Serial.print(",");//Y axis : ");
  Serial.print(y);
  Serial.print(",");//Z axis : ");
//  Serial.println(on);
  Serial.println(z);
  on++;
  if (on == 300)
    on = -1;
}
//else
//Serial.println(accel.read(SYSMOD_SLEEP), HEX);
//delay(10);
//    Serial.println(accel.read(SMOD_LOW_POWER));
    }
//    else
//Serial.println(accel.read(SYSMOD_SLEEP), HEX);
//delay(10);

//   }
//   else
//    delay(1000);
//   if ( on % 1000 == 0){
//    delay(100000);Serial.println("you're in");}
//   accel.sleep();
//  on++;
// }


/*
  // Portrait/Landscape orientation interrupt?
  if(intSource & SRC_LNDPRT_MASK)
  {
    status = accel.readPlStatus();
    Serial.print("PL status : ");
    Serial.println(status, HEX);
  }
  */
//  // Pulse detection interrupt?
//  if(intSource & SRC_PULSE_MASK)
//  {
//    status = accel.readPulseSource();
//    if (status == 0xC0){
//    Serial.print("TAP status : ");
//    Serial.println(status, HEX);}
//  }
  /*
  //
  if(intSource & SRC_FF_MT_MASK)
  {
    status = accel.readFreeFallSource();
    Serial.print("FFMT status : ");
    Serial.println(status, HEX);
  }
  if(intSource & SRC_ASLP_MASK)
  {
    Serial.println("Auto-WAKE event");
  }
  else
  {
    // Still doing something until the interrupt pin goes high again
  }
*/
}

