//#define TRUE 1   //add by Tate (need to include when outside of the arx frame work)
//#define FALSE 0  //add by Tate (need to include when outside of the arx frame work)
#define debug      TRUE    // comment #defines out when moved back to arxrobot_firmware
#define aTechTop   TRUE    // AtechTop
unsigned long nextOxygenReading = millis() + 60000;  // current time + 1 minute, data type 32-bit unsigned*******************times need to change 
unsigned long counter1 = millis() + 1000;  // counter for red LED blinking
unsigned long counter2 = millis() + 50;  // counter for red LED blinking
// oximeter original code from Mohammad Jabbar http://portal.fke.utm.my/fkelibrary/files/mohammadjabbarbinhusin/2012/9_MOHAMMADJABBARBINHUSIN2012.pdf 
#define logf   log
int ledPin = 7;
int sensorPin = 3;
int temp=A1;

double alpha = 0.75;
int period = 20;
double change = 0.0;

void setup_pulseOximeter(){
  pinMode(ledPin, OUTPUT);
}
/*
void loop() {
    #if aTechTop
    
        if(millis() > counter1){
          digitalWrite(ledPin, HIGH); 
        }
      
        if(millis() > counter2){
          digitalWrite(ledPin, LOW);
        }
    
      if(millis() > nextOxygenReading){
        nextOxygenReading = millis() + 600;   // current time + 1 minute, data type 32-bit unsigned
          

     
        static double oldValue = 0;
        static double oldChange = 0;
        double rawValue = analogRead(sensorPin);
        double value = alpha * oldValue + (1 - alpha) * rawValue;
        change = value - oldValue;
        digitalWrite(ledPin, (change < 0.0 && oldChange > 0.0));
        float Tred;
        float Tinf;
        int oxg;
      
        //int reading = analogRead(temp);
        //float voltage = reading * 5.0;
        //voltage /= 1024.0;
      
        //float temperatureC = (voltage) * 100;
      
       // logarithmic calculation to oxigen saturation 
        Tred=1/value;
        Tinf=1/rawValue;
        oxg=int((log(Tred)/log(Tinf))*100);
                
        oldValue = value;
        oldChange = change;
      
      //  sendWordPacket(TEMP_SENSOR_ID, oxg); // distance sensor data package (need to commond it out when not connecting with arx frame work)
        #if debug 
          Serial.println("IR led intensity      Red led intensity       oxg");
          Serial.print("           ");
          Serial.print(rawValue);
        
          Serial.print("           ");
          Serial.print(value);
          
          Serial.print("           ");
          Serial.print(oxg);
        
          Serial.println("    ");
          
        #endif 
    }
  #endif
}
*/

