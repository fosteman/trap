//BOMB1 v0.7
//made by Tim Fosteman. 11/2017
//IF u have any copyright issues - call my lawyer
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
const int A=0xaaaa;// blowbomb1
const int B=0xbbbb;// blowbomb2
const int C=0xcccc; //blow bomb3
boolean alreadyblown=false;
boolean blow=false;
const byte adr1[6] = "01111"; // im writing on it
const byte adr2[6] = "00001"; // im reading it
RF24 radio(2, 3);

int Z;
/*
int analog;
float V = 0.0;
*/
const int ignitor = 4;
 //const int find_led = 5;
void setup() {
  pinMode(ignitor, OUTPUT);
  //pinMode(find_led, OUTPUT);
  radio.begin();
 radio.setRetries(5,15);
 radio.setDataRate(RF24_250KBPS);
 radio.setPALevel(RF24_PA_MAX);
 //setCRCLength( RF24_CRC_8 ) ;
 
  radio.openReadingPipe(1,adr2);
  radio.startListening();
  Z=0;
}
void loop() {
  liste();
  blowbomb();
  //batstat();    
  }

void liste() {
  if (radio.available()) {
    radio.read(&Z, sizeof(Z));
    if (Z == A) { blowbomb(); } else {delay(100);  Z=0; }
}
}
void blowbomb() {
    if (alreadyblown == false) {
           alreadyblown=true;
           digitalWrite(ignitor, HIGH);
           delay(5000);
           digitalWrite(ignitor, LOW); } 
                     
}
/*
 * 
void batstat() { //transmitt battery voltage
  if (radio.available()) {
    radio.read(&Z, sizeof(Z));
           if (Z == C) {
            radio.stopListening();
            digitalWrite(3, HIGH);
            delay(1000);
            digitalWrite(3, LOW);
         radio.openWritingPipe(adr1);
         int analog = analogRead(A0);
         float V = analog * (5.0 / 1023.0);
         radio.write(&V,sizeof(V));
         delay(50);
         radio.startListening();
           }
            
           }
}
   /*else {                  //if base is looking for me - transieve rdy status.
        if (A == B) { // if it recieved before exlosion - then id like to see if this bomb is alive and also its battery volatge
          digitalWrite(find_led, HIGH);
          delay(10000);
          digitalWrite(find_led, LOW);
          // pin 5 high
         // radio.stopListening();
         // radio.openWritingPipe(adr1);
         // int analog = analogRead(A0);
         // float V = analog * (5.0 / 1023.0);
         // radio.write(&V,sizeof(V));
         // delay(50);
         // radio.startListening();
                     }
            }
            */
                             

/*  if (alreadyblown == false) { //wut have i just didi lul :ddxddd
    alreadyblown=true;
    radio.stopListening();
    radio.openWritingPipe(pipe2);
    delay(10000); // every 10 secs bomb writes to pipe2.
    digitalWrite(find_led, HIGH);
  }
  
  else {
    radio.write(&B,sizeof(B));
    delay(30000);
                      //also it has to transmit it's battery voltage somehow xddd
  }
  */

///////end////////


