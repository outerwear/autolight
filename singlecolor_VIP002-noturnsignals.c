/*
 * LED Control code for brake lights, turn signals, and VIP
 * Author: Michael Coates
 * v001   20150714    File created.
 */

#include <SPI.h>
 
#define NUMLED 16
#define LASTLED 15

// Global variables
const int VIP = 5;
const int latchPin = 10;
const int clockPin = 13;
const int dataPin = 11;
const int tlp = 9;
const int tcp = 12;
const int tdp = 8;
int outputEnablePin = 3;
int VIPmode    = 0;
boolean registers[NUMLED]; //red
int SS1 = 10;

void setup(){
  pinMode(latchPin, OUTPUT);
  pinMode(outputEnablePin, OUTPUT);
  pinMode(tlp, OUTPUT);
  //pinMode(tcp, OUTPUT);
  pinMode(tdp, OUTPUT);
  pinMode(VIP, INPUT);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2);
}

void loop(){
  VIPmode = digitalRead(VIP);
  
  //if(VIPmode == HIGH) {
    
    swipe();
    stripe_f();
    swipeL();
    knight();
    swipeR();
    fatten();
    big_slide();
    //fade();
  //}
  randomSeed(analogRead(A0));
}

void fade(){
  for(int x = 0; x < 3; x++){
    for(int j = 0; j <255; j++){
      analogWrite(outputEnablePin,j);
      delay(2);
    }
    for(int j = 255; j >= 0; j--){
      analogWrite(outputEnablePin,j);
      delay(2);
    }
  }
}

void strobe(){
  int rled = random(NUMLED);
  char usedled[NUMLED];
  memset(usedled,'\0',NUMLED);
  for(int i = 0; i < NUMLED; i++){
    while(usedled[rled] == 'x'){
      rled = random(NUMLED);
    }
    usedled[rled] = 'x';
    for(int j = 0; j < 6; j++){
      registers[rled] = LOW;
      //writereg(clockPin, dataPin, latchPin, registers);
      delay(50);
      registers[rled] = HIGH;
      //writereg(clockPin, dataPin, latchPin, registers);
      delay(50);
    }
    rled = random(NUMLED); 
  }
}

void swipe(){
  unsigned int x = 1;
  unsigned int y = 0;
  for(int i = 0; i < ((NUMLED/2)*3)+1; i++){
    SPI.transfer(y);
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
    SPI.transfer(x);
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
    if (x < 255 && x != 0){
      x = (x << 1) | 1;
    } else if (x > 255 && x < 65280){
      x = x << 1;
      y = (y << 1) | 1;
    } else if (x == 255){
      x = x << 1;
      y = 1;
    } else {
      y = y << 1;
    }
    delay(20);
  }
  y = 128;
  for(int i = 0; i < ((NUMLED/2)*3)+1; i++){
    SPI.transfer(y);
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
    SPI.transfer(x);
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
    if (y > 127 && y < 255){
      y = (y >> 1) | 128;
    } else if (y > 0){
      y = y >> 1;
      x = (x >> 1) | 128;
    } else if (y == 255){
      y = y >> 1;
      x = 128;
    } else {
      x = x >> 1;
    }
    delay(20);
  }
}

void stripe_f(){
  unsigned int a = 204;
  for(int i=0; i<(NUMLED/2); i++){
    if((i%4) == 0){
      a = 204; 
    }
    for(int j=0; j<5; j++){
      SPI.transfer(a);
      digitalWrite(latchPin, LOW);
      digitalWrite(latchPin, HIGH);
      SPI.transfer(a);
      digitalWrite(latchPin, LOW);
      digitalWrite(latchPin, HIGH);
      delay(20);
      SPI.transfer(255);
      digitalWrite(latchPin, LOW);
      digitalWrite(latchPin, HIGH);
      SPI.transfer(255);
      digitalWrite(latchPin, LOW);
      digitalWrite(latchPin, HIGH);
      delay(8);
      SPI.transfer(a);
      digitalWrite(latchPin, LOW);
      digitalWrite(latchPin, HIGH);
      SPI.transfer(a);
      digitalWrite(latchPin, LOW);
      digitalWrite(latchPin, HIGH);
      delay(20);
    }
    a = a >> 1;
  }
}

void knight(){
  unsigned int x = 1, y = 128;
  for(int i=0; i<NUMLED; i++){
    SPI.transfer(y);
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
    SPI.transfer(x);
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
    delay(55);
    if(i<(NUMLED/2 - 1)){
      x = x << 1;
      y = y >> 1;
    } else {
      x = x >> 1;
      y = y << 1;
    }
  }
}

void fatten(){
  unsigned int x = 128, y = 1;
  for(int i=0; i<NUMLED; i++){
    SPI.transfer(y);
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
    SPI.transfer(x);
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
    if(i<(NUMLED/2 - 1)){
      x = (x >> 1) | 128;
      y = (y << 1) | 1;
    } else {
      x = x << 1;
      y = y >> 1;
    }
    delay(30);
  }
}

void big_slide(){
// 00001111
// 11110000
  unsigned int a = 0, b = 255;
  for(int i=0; i<8; i++){
    SPI.transfer(b);
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
    SPI.transfer(a);
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
    a = (a << 1) | 1;
    b = (b << 1);
    delay(50);
  }
  a = 255;
  b = 0;
  for(int i=0; i<8; i++){
    SPI.transfer(b);
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
    SPI.transfer(a);
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
    a = (a >> 1);
    b = (b >> 1) | 128;
    delay(50);
  }
}

void swipeL(){
  unsigned int x = 1;
  unsigned int y = 0;
  for(int i = 0; i < ((NUMLED/2)*3)+1; i++){
    SPI.transfer(y);
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
    SPI.transfer(x);
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
    if (x < 255 && x != 0){
      x = (x << 1) | 1;
    } else if (x > 255 && x < 65280){
      x = x << 1;
      y = (y << 1) | 1;
    } else if (x == 255){
      x = x << 1;
      y = 1;
    } else {
      y = y << 1;
    }
    delay(20);
  }
}
void swipeR(){
  unsigned int x = 0, y = 128;
  for(int i = 0; i < ((NUMLED/2)*3)+1; i++){
    SPI.transfer(y);
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
    SPI.transfer(x);
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
    if (y > 127 && y < 255){
      y = (y >> 1) | 128;
    } else if (y > 0){
      y = y >> 1;
      x = (x >> 1) | 128;
    } else if (y == 255){
      y = y >> 1;
      x = 128;
    } else {
      x = x >> 1;
    }
    delay(20);
  }
}

