
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); //TX, RX
void setup() {
   Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
   
   if(Serial.available() > 0){//Read from serial monitor and send over UM402
    String input = Serial.readString();
    mySerial.println(input);    
  }
 
  if(mySerial.available() > 1){//Read from UM402 and send to serial monitor
    String input = mySerial.readString();
    Serial.println(input);    
  }
  delay(20);
}
