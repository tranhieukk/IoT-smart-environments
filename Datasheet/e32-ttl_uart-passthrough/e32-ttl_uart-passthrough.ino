/**
 * E32-TTL UART Passthrough
 *
 * @author Pasakorn Tiwatthanont, AKA. iPAS.
 * @date 19 May 2017
 *
 * This code is adopted from:
 * @see http://spacetinkerer.blogspot.com/2011/02/serial-port-echo-with-arduino.html, and
 * @see https://github.com/tienfuc/E32-TTL.
 *
 * If you need a soft serial (UART) function, please follow
 * @see http://www.arduino.cc/en/Tutorial/SoftwareSerialExample.
 */

#include <SoftwareSerial.h>

#define M0      7
#define M1      8
#define AUX     12

#define SOFT_RX 10
#define SOFT_TX 11
SoftwareSerial softSerial(SOFT_RX, SOFT_TX);  // RX, TX

#define MAX_TX_SIZE 58


// The setup function runs once when you press reset or power the board
void setup() {
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(AUX, INPUT);

  pinMode(SOFT_RX, INPUT);
  pinMode(SOFT_TX, OUTPUT);

  Serial.begin(9600);
  softSerial.begin(9600);

  // Mode 0 | normal operation
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
}


// The loop function runs over and over again forever
void loop() {

  /**
   * Coming from normal UART
   */
  if (Serial.available() && digitalRead(AUX)) {
    char buf[MAX_TX_SIZE];
    int cnt = 0;

    do {
      buf[cnt++] = Serial.read();
    } while (Serial.available() && cnt < MAX_TX_SIZE);

    softSerial.write(buf, cnt);
  }

  /**
   * Coming from software UART
   */
  if (softSerial.available()) {
    char buf[MAX_TX_SIZE];
    int cnt = 0;

    do {
      buf[cnt++] = softSerial.read();
    } while (softSerial.available() && cnt < MAX_TX_SIZE);

    Serial.write(buf, cnt);
  }

}
