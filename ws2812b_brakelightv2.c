/* 
 *  Author: Michael Coates 
 *  Purpose: WS2812B LED tail lights for SUBARU IMPREZA WRX/STI GR (HATCH)
 *  
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 5
#define NUMPIXELS 56

const int buttonPin = 2;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripb = Adafruit_NeoPixel(NUMPIXELS, PIN+1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripc = Adafruit_NeoPixel(NUMPIXELS+21, PIN+5, NEO_GRB + NEO_KHZ800);
float vPow = 4.7;
float r1 = 100000;
float r2 = 10000;
int buttonState = 0;
 
void setup() {
  pinMode(buttonPin, INPUT);
   /*Serial.begin(9600);
   Serial.print("\x1B");
   Serial.print("[2J");
   Serial.print("\x1B");
   Serial.println("[H");
   Serial.println("--------------------");
   Serial.println("DC VOLTMETER");
   Serial.print("Maximum Voltage: ");
   Serial.print((int)(vPow / (r2 / (r1 + r2))));
   Serial.println("V");
   Serial.println("--------------------");
   Serial.println("");
*/
   delay(4000);
   strip.begin();
   stripb.begin();
   stripc.begin();
   strip.show();
   stripb.show();
   stripc.show();  
   startup_seq();  
 }
 
void loop() {
   float v = (analogRead(0) * vPow) / 1024.0; // parking lights (green wire)
   float v2 = v / (r2 / (r1 + r2));
   float z = (analogRead(1) * vPow) / 1024.0; // brakes (red wire)
   float z2 = z / (r2 / (r1 + r2));
   
/*   Serial.print("\x1B");
   Serial.print("[1A");  
   Serial.println(v2);
*/ 
  if(z2 > 2.5){
    for(int i=0;i<NUMPIXELS+21;i++){
      if(i<NUMPIXELS){
      strip.setPixelColor(i, strip.Color(245,0,0)); 
      stripb.setPixelColor(i, stripb.Color(245,0,0));
      stripc.setPixelColor(i, stripc.Color(245,0,0));
      } else {
        stripc.setPixelColor(i, stripc.Color(245,0,0));
      }
    }
    strip.show();
    stripb.show();
    stripc.show();
  } else {
    if(v2 > 2.5){
      for(int i=0;i<NUMPIXELS+21;i++){
        if(i<NUMPIXELS){
          strip.setPixelColor(i, strip.Color(70,0,0)); 
          stripb.setPixelColor(i, stripb.Color(70,0,0));
          stripc.setPixelColor(i, stripc.Color(70,0,0));
        } else {
          stripc.setPixelColor(i, stripc.Color(70,0,0));
        }
      }
      strip.show();
      stripb.show();
      stripc.show();
    } else {
      for(int i=0;i<NUMPIXELS+21;i++){
        if(i<NUMPIXELS){
          strip.setPixelColor(i, strip.Color(0,0,0));
          stripb.setPixelColor(i, stripb.Color(0,0,0));
          stripc.setPixelColor(i, stripc.Color(0,0,0));
        } else {
          stripc.setPixelColor(i, stripc.Color(0,0,0));
        }
      }
      strip.show();
      stripb.show();
      stripc.show();
    }
  }  

  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
   /* colorWipe(strip.Color(255, 0, 0), 50); // Red
    colorWipe(strip.Color(0, 255, 0), 50); // Green
    colorWipe(strip.Color(0, 0, 255), 50); // Blue */
    theaterChase(strip.Color(127, 127, 127), 50); // White
    theaterChase(strip.Color(127, 0, 0), 50); // Red
    theaterChase(strip.Color(0, 0, 127), 50); // Blue 
    rainbow(20);
    rainbowCycle(20);
    theaterChaseRainbow(50);
    colorfade(10);
    buttonState = LOW;
  } 
}

void startup_seq(){
  int i;
  for(i=0; i < NUMPIXELS; i++){
    strip.setPixelColor(i, strip.Color(250,0,0));
    stripb.setPixelColor(i, stripb.Color(250,0,0));
    stripc.setPixelColor(i, stripc.Color(250,0,0));
    strip.show();
    stripb.show();
    stripc.show();
    delay(15);
    strip.setPixelColor(i, strip.Color(0,250,0));
    stripb.setPixelColor(i, stripb.Color(0,250,0));
    stripc.setPixelColor(i, stripc.Color(0,250,0));
    strip.show();
    stripb.show();
    stripc.show();
    delay(15);
    strip.setPixelColor(i, strip.Color(0,0,250));
    stripb.setPixelColor(i, stripb.Color(0,0,250));
    stripc.setPixelColor(i, stripc.Color(0,0,250));
    strip.show();
    stripb.show();
    stripc.show();
    delay(15);
    strip.setPixelColor(i, strip.Color(0,0,0));
    stripb.setPixelColor(i, stripb.Color(0,0,0));
    stripc.setPixelColor(i, stripc.Color(0,0,0));
    strip.show();
    stripb.show();
    stripc.show();
    delay(15);
  }
  for(i=NUMPIXELS; i<NUMPIXELS+21; i++){
    stripc.setPixelColor(i, stripc.Color(250,0,0));
    stripc.show();
    delay(15);
    stripc.setPixelColor(i, stripc.Color(0,250,0));
    stripc.show();
    delay(15);
    stripc.setPixelColor(i, stripc.Color(0,0,250));
    stripc.show();
    delay(15);
    stripc.setPixelColor(i, stripc.Color(0,0,0));
    stripc.show();
    delay(15);
  }
}

void flash(){
  int i, j, k;


}

void colorfade(uint8_t wait){
  int k;
  for(k=0; k < 250; k++){
    for(uint16_t i=0; i<NUMPIXELS; i++){
      strip.setPixelColor(i,strip.Color(k,k,0));
      stripb.setPixelColor(i,stripb.Color(k, 0, k));
      strip.show();
      stripb.show();
    }
    delay(wait);
  }
  for(k=0; k < 250; k++){
    for(uint16_t i=0; i<NUMPIXELS; i++){
      strip.setPixelColor(i,strip.Color(0,k,k));
      stripb.setPixelColor(i,stripb.Color(k, k/3, k/2));
      strip.show();
      stripb.show();
    }
    delay(wait);
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    stripb.setPixelColor(i, c);
    strip.show();
    stripb.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
      stripb.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    stripb.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      stripb.setPixelColor(i, Wheelb(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    stripb.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
        stripb.setPixelColor(i+q, c);
      }
      strip.show();
      stripb.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
        stripb.setPixelColor(i+q, 0);
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        stripb.setPixelColor(i+q, Wheelb( (i+j) % 255));
      }
      strip.show();
      stripb.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
        stripb.setPixelColor(i+q, 0);
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

uint32_t Wheelb(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return stripb.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return stripb.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return stripb.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void flash(uint32_t col, uint16_t num, int pix, uint8_t flag){
  for(uint16_t i=0; i < num; i++){
    if(flag){
      strip.setPixelColor(pix,strip.Color(0,0,0));
      strip.show();
      delay(8);
      strip.setPixelColor(pix,col);
      strip.show();
    } else {
      stripb.setPixelColor(pix,strip.Color(0,0,0));
      stripb.show();
      delay(8);
      stripb.setPixelColor(pix,col);
      stripb.show();
    }
  }
}

