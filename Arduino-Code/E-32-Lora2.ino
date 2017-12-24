/*  8: M0
 *  9: M1
 * 10: RX
 * 11: TX
 * 12: AUX
 */


#include <SoftwareSerial.h>



#define M0 8
#define M1 9
#define SOFT_TX 10
#define SOFT_RX 11
#define AUX 12

#define MODE_SWITCH 13

SoftwareSerial softSerial(SOFT_RX, SOFT_TX); // RX, TX
char byte_buffer[3];
char output_buffer[7];
// the setup function runs once when you press reset or power the board
void setup() {
  
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(SOFT_RX, INPUT);
  pinMode(SOFT_TX, OUTPUT);  
  pinMode(AUX, INPUT);
  pinMode(MODE_SWITCH, INPUT);
  
  Serial.begin(9600);
  softSerial.begin(9600);


  // mode 0
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);

  byte_buffer[0] = '\0';
  output_buffer[0] = '\0';

}

#define MODE0 "z"
#define MODE1 "x"
#define MODE2 "c"
#define MODE3 "v"

// set E32-TTL mode
char set_mode(char mode) {
  char m0 = 0;
  char m1 = 0;
  
  switch(mode) {
    // working
    case 0: 
      m0=0;
      m1=0;
      break;
    // wake-up
    case 1: 
      m0=0;
      m1=1;
      break;
    // power-saving
    case 2:
      m0=1;
      m1=0;
      break;
    // sleep
    case 3: 
      m0=1;
      m1=1;
      break;   
    default:
      return false;
  }

  digitalWrite(M0, m0);
  digitalWrite(M1, m1);      
  
  return true;
}

// the loop function runs over and over again forever
void loop() {
  if(Serial.available()>0) {
    delay(10);
    char input = Serial.read();
    
    if(input == '\n') {          

      //Serial.println(output_buffer);
      softSerial.write(output_buffer);
      output_buffer[0] = '\0';
      delay(100);

    } else {
      //

      
      size_t len_byte_buffer = strlen(byte_buffer);
      byte_buffer[len_byte_buffer] = input;       
      byte_buffer[len_byte_buffer+1] = '\0';       
      
      
      if( len_byte_buffer == 1 ) {                
        int output_byte = strtoul(byte_buffer, NULL, 16);
        Serial.println(output_byte);
        Serial.println(byte_buffer);
        byte_buffer[0] = '\0';
        size_t len_output_buffer = strlen(output_buffer);
        output_buffer[len_output_buffer] = output_byte;        
      } 
         
     
      
      
    }

    

    
    
    //char high_byte = Serial.read();
    
    
    //Serial.println(output);
  }

  if(softSerial.available()>0) {
    // char input = softSerial.readBytesUntil('\0', buffer, 2);
    delay(10);    
    char input = softSerial.read();
    
    //int output = strtoul(&input, NULL, 16);
    char one_byte[3]="";    
    sprintf(&one_byte[0], "%02x", input);
    
    Serial.println(one_byte);
    //softSerial.print(output);
  }


  // 
  int mode = digitalRead(MODE_SWITCH);
  if( mode == LOW ) { 
    // mode 0
    digitalWrite(M0, LOW);
    digitalWrite(M1, LOW);
  } else {
    // mode 3
    digitalWrite(M0, HIGH);
    digitalWrite(M1, HIGH);

 
  }
 
  

 
  
}
