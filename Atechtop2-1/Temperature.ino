// code works outside of the arx file
#include <OneWire.h>
// https://www.pjrc.com/teensy/td_libs_OneWire.html

#define debug      TRUE    // comment #defines out when moved back to arxrobot_firmware
#define aTechTop   TRUE    // AtechTop

//  #define TRUE 1   //add by Tate (need to include when outside of the arx frame work)
//   #define FALSE 0  //add by Tate (need to include when outside of the arx frame work)

int DS18S20_Pin = 5; //DS18S20 Signal pin on digital 5

unsigned long nextTempReading = millis() + 60000;  // current time + 1 minute, data type 32-bit unsigned 

//Temperature chip i/o
OneWire ds(DS18S20_Pin); // on digital pin 2
/*
void setup(void) {   // comment out when moved back to arxrobot_firmware
 Serial.begin(9600);
}
*/
/*
void loop(void) {   // moved to sendData method in telemetery in arxrobot_firmware
 
  #if aTechTop 
    if(millis() > nextTempReading){
      nextTempReading = millis() + 60000;   // current time + 1 minute, data type 32-bit unsigned
      
      // find out what temperature data looks like signed 16-bits 
      // range expected
      // need to casr float to expected datatype
      
      float temperature = getTemp();
      int temp = (int)temperature;
      sendWordPacket(TEMP_SENSOR_ID, temp); // distance sensor data package; need to commond it out when outside of arx file
      #if debug 
        Serial.println(temp);  
      #endif 
    }
  #endif
  
}
*/

float getTemp(){
   //returns the temperature from one DS18S20 in DEG Celsius
  
   byte data[12];
   byte addr[8];
  
   if ( !ds.search(addr)) {
     //no more sensors on chain, reset search
     ds.reset_search();
     return -1000;
   }

   if ( OneWire::crc8( addr, 7) != addr[7]) {
     Serial.println("CRC is not valid!");
     return -1000;
   }

   if ( addr[0] != 0x10 && addr[0] != 0x28) {
     Serial.print("Device is not recognized");
     return -1000;
   }

   ds.reset();
   ds.select(addr);
   ds.write(0x44,1); // start conversion, with parasite power on at the end 
   //device reads the internal ADC,and when this process is complete, it copies the data into the Scratchpad registers
  
   byte present = ds.reset();
   ds.select(addr);  
   ds.write(0xBE); // Read Scratchpad

   for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
   }
 
   ds.reset_search();
   
   //convert the HEX code to a temperature value
   byte MSB = data[1];
   byte LSB = data[0];

   float tempRead = ((MSB << 8) | LSB); //using two's compliment
   float TemperatureSum = tempRead / 16;
   
   return TemperatureSum;
 
}
