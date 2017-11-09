//made by Tim Fosteman. 11/2017
//TRANSMITTER MOTHER-BASE.--------LIBRARIES--------------
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <ShiftRegister74HC595.h>
ShiftRegister74HC595 sr (1, 3, 4, 5); //data, clock, latch
// --------CONSTANTS
//const int power_led =  ;      //power status
//const int bomb1rdy_led = ;  //bomb 1 status led (on - rdy to blow, off - not connected).




const int bomb1blow_button = 6;
const int bomb2blow_button = 7;
const int bomb3blow_button = 8;
const int key_switch = 9; 




RF24 radio(7, 8);

/*const uint64_t pipe1=0xC0B1; //TO write into bomb1
const uint64_t pipe2=0xC1B1; //TO read from bomb1
const uint64_t pipe3=0xC0B2; //TO write into bomb2
const uint64_t pipe4=0xC1B2; //TO read from bomb2
const uint64_t pipe5=0xC0B3; //TO write into bomb3
const uint64_t pipe6=0xC1B3; //TO read from bomb3
*/
const byte adr1[6] = "01111"; //to read from all bombs
const byte adr2[6] = "00001"; //write to bomb1
/*const byte adr3[6] = "00002"; //write to bomb2
const byte adr4[6] = "00003"; //write to bomb3
const byte adr5[6] = "00004"; //write to bomb4
const byte adr6[6] = "00005"; //write to bomb5
const byte adr7[6] = "00006"; //write to bomb6
*/
boolean bomb1status = false;      // if true - bomb 1 is exloded, false - remains stealth.
boolean bomb2status = false;
boolean bomb3status = false;
boolean bomb4status = false;
boolean bomb5status = false;
boolean bomb6status = false;
const int A=0xaaaa;// blowbomb1
const int B=0xbbbb;// blowbomb2
const int C=0xcccc; //blow bomb3
/*const int A=0xbbbb; //N1// these are bomb1-6 explode signals
const int A=0xabbb; //N2
const int A=0xaaaa; //N3
const int A=0xaaaa; //4
const int A=0xaaaa; //5
const int A=0xaaaa; //6
*/
/*int Z;
// float bomb1v = 0.0;
*/
void setup() {
  //radio init
radio.begin();
radio.setDataRate(RF24_250KBPS);
radio.setPALevel(RF24_PA_MAX);
radio.setRetries(5,15);
//setCRCLength(RF24_CRC_8);
radio.openReadingPipe(1,adr1);
radio.startListening();
//  pinMode(power_led, OUTPUT);
 // pinMode(bomb1rdy_led, OUTPUT);
 // pinMode(bomb1status_led, OUTPUT); //if HIGH - BOMB IS BLOWN.
 // pinMode(bomb1blow_button, INPUT); //if HIGH - BOMB is about to be BLOWN!!!
 // pinMode(bomb1status_button, INPUT);
  //pinMode(bomb1find_button, INPUT);
 // pinMode(bomb1status_sw, INPUT);
//  digitalWrite(power_led, HIGH);
//        BOMB LEVERS   //
pinMode(bomb1blow_button, INPUT);
pinMode(bomb2blow_button, INPUT);
pinMode(bomb3blow_button, INPUT);
//pinMode(bomb4blow_button, INPUT);
//pinMode(bomb5blow_button, INPUT);

sr.setAllHigh();
delay(300);
sr.setAllLow();

}

//========================================

void loop() {
  leverchecker();
/*  bomb1find();
  blowbomb2();
  findbomb();
  statusbomb();
  testblow();
  test();
  */
}


void leverchecker() {
  if (digitalRead(bomb1blow_button == HIGH))  { // its over 9000!!!!!!!11 bombs you can add here
    sr.set(1, HIGH);  //debug feature
    if (digitalRead(key_switch == HIGH)) {
      blowbomb1();
    }
    }
  else {  sr.set(1,LOW); }     // keep calm duuuude


  //2
  if digitalRead(bomb2blow_button == HIGH)  { // its over 9000!!!!!!!11 bombs you can add here
    sr.set(2, HIGH);  //debug feature
    if {
    digitalRead(key_switch == HIGH) {
      blowbomb2();
    }
    }
  }
  else {  sr.set(2,LOW); }


  //3

  if digitalRead(bomb3blow_button == HIGH)  { // its over 9000!!!!!!!11 bombs you can add here
    sr.set(3, HIGH);  //debug feature
    if {
    digitalRead(key_switch == HIGH) {
      blowbomb3();
    }
    }
  }
  else {  sr.set(3,LOW); }
}

void blowbomb1() { //SWITCH TO BLOW BOMB1 // now, it might be made better with multiple bombs at once or watever. sry for lazyness i put in this project. (money would have turn things around btw :DDD) 
  if (bomb1status == false) {
    radio.stopListening();
    radio.openWritingPipe(adr2); // to be able to write to bomb1
    delay(50);
    if ((radio.write(&A,sizeof(A))) == true) {
      sr.set(4, HIGH); //debug feature
      bomb1status=true;
      radio.startListening();
    }
    /*  if (radio.available() == true) {
      radio.read(&Z,sizeof(Z));
      if (Z == B) {
        digitalWrite(bomb1status_led,HIGH); // WIP.
      } */
    }
}

void blowbomb2() {  if (bomb2status == false) {
    radio.stopListening();
    radio.openWritingPipe(adr2);
    delay(50);
    if ((radio.write(&B,sizeof(B))) == true) {
      sr.set(5, HIGH); //debug feature
      bomb2status=true;
      radio.startListening();
    }
    }
}

void blowbomb3() {  if (bomb3status == false) {
    radio.stopListening();
    radio.openWritingPipe(adr2);
    delay(50);
    if ((radio.write(&C,sizeof(C))) == true) {
      sr.set(6, HIGH); //debug feature
      bomb3status=true;
      radio.startListening();
    }
    }
}

/*void bomb1batstat() {
  if (digitalRead(bomb1status_sw) == HIGH) {
    delay(500);//pin4`
    if (digitalRead(bomb1status_sw) == HIGH) {
      radio.stopListening();
    radio.openWritingPipe(adr2);
    radio.write(&C, sizeof(C));
    radio.startListening();
    if (radio.available() == true) {
      radio.read(&bomb1v, sizeof(bomb1v));
      delay(500);
      //somhow i need to indicate it. liqiud crystal mb?
    }
    }
    
  }
  */

/*void bomb1find() {
  if (bomb1status == true) {
    if (radio.available()) {
      (radio.read(&Z,sizeof(Z));
      if (Z==B)
      {
        
      }
    }
    */
    
//
/*void statusbomb() {
  if (blow == false) 
  {
    radio.startListening();
    radio.read(&A,sizeof(A));
    radio.stopListening();
    digitalWrite(ignitor,blow);
    delay(100);
    if(A==0xaaaa){
      blow=true;
      radio.write(B
    }
}
  
///////////////


void blowbomb1() {
  if (digitalRead(bombblow_button == HIGH)) {
    radio.write(&temp2, sizeof(temp2))
  }
}

void blowbomb() {
  if (digitalRead(bombblow_button == HIGH) {
    msg[0] = 100;
    radio.write(msg, 1);
    //RADIO TRANSMITT TO BLOW THE BOMB
  }
  
}
void findbomb() {
  if (digitalRead(bomb1findme == HIGH) {
    msg
    //RADIO TRASMITT TO LIGHT A LED ON THE BOMB
  }
}
void statusbomb() {
  if (digitalRead(bomb1status_button, HIGH) {
    //RADIO TRANSMITT TO OBSERVE VOLTAGE ON BATTERY.
  }
}w

//the end, mazafakers.
*/
