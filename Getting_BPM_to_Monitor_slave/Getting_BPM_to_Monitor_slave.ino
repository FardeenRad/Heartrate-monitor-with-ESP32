#include<SoftwareSerial.h>

#define USE_ARDUINO_INTERRUPTS true    
#include <PulseSensorPlayground.h>      

//  Variables
const int PulseWire = A0;       
const int LED13 = 13;          
int Threshold = 520;           
int BPM;
                               
SoftwareSerial BPMSerial(2,3);  // TX = 3, RX = 2                     
PulseSensorPlayground pulseSensor; 


void setup() {   

  Serial.begin(115200);         
  BPMSerial.begin(115200);

  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       
  pulseSensor.setThreshold(Threshold);    
  pulseSensor.begin(); 

}



void loop() {
  readBPM();
  Serial.println(BPM);
  BPMSerial.write(BPM);
    delay(1000);                    
}


void readBPM(){
  volatile int myBPM = pulseSensor.getBeatsPerMinute();  
                                               
  if(pulseSensor.sawStartOfBeat()){
    BPM = myBPM;               
    }
}
