/* The following two libraries are included with the Arduino IDE  */
#include <SPI.h>       // supports SPI serial communication and defines analog pins
#include <EEPROM.h>
#include <Wire.h>      // I2C support (currently not implemented)
// #include <L3G4200D.h>  // 3-axis Gyro (currently not implemented)

#define FALSE 0        // LOW
#define TRUE  1        // HIGH

/**************** Robot Configuration **************
 * Set Rover, Pinouts, Connection Type, and Pinger *
 ***************************************************/
#include "pinouts_robot.h"    // replace with your pinout

#define Rosco FALSE
#define PaperBot FALSE
#define bluetooth FALSE       // Leonardo class rovers - Serial used for USB, Serial1 for bluetooth (i.e., USART)
#define pinger FALSE          // FALSE if no ultrasonic sensor is used.
#define debug  FALSE
#define aTechTop   TRUE           // AtechTop

// note: #define is a text substitution pre-processor directive
 
/**************** Global Variables ****************
 * source: Found in CommunicationRobotPilot Folder  *
 ***************************************************/
const int16_t FLAG = -128;  // value returned by readFuelGauge when called
                            // by sendDataon undervoltage condition
// Timer Variable
unsigned long timer;        // unsigned 32-bit

boolean collisionDetection = FALSE;
 
void setup(){
  Serial.begin(9600);      // legacy rovers operated at 57600
  #if bluetooth
  Serial1.begin(9600);
  #endif
  
  /*
  while (!Serial) {
    ; // wait for USB serial port to connect. Needed for Leonardo only
  }
  */
  
  timer = millis();        // telemetry  
  // init_servos();        // Rosco uses servos
  
  pinMode(led, OUTPUT);    // initialize LED indicator as an output.
 
  #if PaperBot
    // Configure motorshield and insure motors are off. 
    // If included in design, turn off collisionDetection
    setup_TB6612FNG();    // sparkfun_TB6612FNG
  #endif
  
  #if aTechTop
    setup_pulsesensor();   //PulseSensorAmped_Arduino_1dor2 
    setup_pulseOximeter(); //pulseOximeter   
  #endif
  
}

void loop(){
  
  #if bluetooth
  if(Serial1.available() ) commandDecoder();  // note: Leonardo does not support serialEvent() handler
  #else
  if(Serial.available() ) commandDecoder();
  #endif
  
  // future: replace with watchdog timer interrupt  ****
  
  if (millis() > getNextPing()){   
    sendWordPacket(EMERGENCY_ID,WATCHDOG_TIMEOUT);
    
    #if bluetooth                                // if packet sent over USART=>bluetooth,  
      Serial.print("Emergency exception 0x0");   // send duplicate data as text to
      Serial.println(WATCHDOG_TIMEOUT,HEX);      // USB=>Arduino IDE Serial Monitor.
    #endif 
    
    // ****** SLEEP PAPERBOT *******
    
    // ##### JEFF CHANGED
    // Until the above-mentioned "SLEEP PAPERBOT" is implemented,
    // let's reset to allow another ping interval to avoid the
    // constant barrage of an exception message on every loop.
    updateNextPing();
    // #####
  }
  
  
  sendData(); // Call to send Data for Control Panel Feedback

  // If using a Pinger detect a collision
  #if pinger == TRUE
      if (collisionDetection){
        if (checkSonar()) {
          // insure motors are off and turn off collisionDetection
          stopMotors();
          collisionDetection = FALSE;   // rover is not moving
          // send Emergency Stop message
        }
      }
  #endif
  
}  // end of loop
