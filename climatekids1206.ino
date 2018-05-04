#include <Servo.h>
#include "Adafruit_NeoPixel.h"

#define PIN_HIGHBIT (3)
#define PIN_LOWBIT  (2)
#define BAUDRATE    (9600)
#define neopixel_16 6
#define neopixel_24 5

unsigned long time;
int boolean_switch = 1;
int vap_switch = 1;
const uint32_t job_period = 500;
int seconds = 0;

int wait = 20;//balance this number with faderate to regulate speed of fade
int faderate = 200;//higher number here for smoother fades

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(16, neopixel_16, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(24, neopixel_24, NEO_GRB + NEO_KHZ800);

// define variables for rotary
volatile int state, prevState = 0, count = 0, prevTurn = 0, turn = 0, energy = 100;
int encoderStates[4][4] = {
 {  0, -1,  1,  0 }, 
 {  1,  0,  0, -1 }, 
 { -1,  0,  0,  1 }, 
 {  0,  1, -1,  0 }, 
};

//define variables for LEDs
int ledhouse = 13, ledwater = 12;

//define variables for vapourizer
Servo myservo;

//define variables for fan/motor 
int motorPin = 4;

void setup() {
  
  pinMode(PIN_HIGHBIT, INPUT);
  pinMode(PIN_LOWBIT, INPUT);
  digitalWrite(PIN_LOWBIT, HIGH);
  digitalWrite(PIN_HIGHBIT, HIGH);
  Serial.begin(BAUDRATE); 
  attachInterrupt(digitalPinToInterrupt(3), rotaryChange, CHANGE);

  //setup for LED
  pinMode(ledhouse, OUTPUT);
  pinMode(ledwater, OUTPUT);
  digitalWrite (ledwater, HIGH);
  digitalWrite (ledhouse, HIGH);

  //setup for vapourizer
  myservo.attach(9);
  myservo.write(180);

  //setup for motors (transistors)
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW);

  //setup for rainbow_neopixel
  strip1.begin();
  strip1.setBrightness(30); //adjust brightness here
  strip1.show(); // Initialize all pixels to 'off'
  strip2.begin();
  strip2.setBrightness(30); //adjust brightness here
  strip2.show(); // Initialize all pixels to 'off'
}

void rotaryChange() {
  
  state = (digitalRead(PIN_HIGHBIT) << 1) | digitalRead(PIN_LOWBIT);
  count += encoderStates[prevState][state];
  turn = count/12 + 1;
  if (turn != prevTurn) {
  energy = energy + 2;    
  }
  prevTurn = turn;
  prevState = state;

}

void loop() {
    //print time
    time = millis();
    delay(1000);             // wait a second so as not to send massive amounts of data
    seconds = time/1000; // converts milliseconds to seconds
    delay(1000);

  //calculate energy wastage 
  if (boolean_switch = 1) {
  static uint32_t previousMillis;
    if (millis() - previousMillis >= job_period) {
        energy--;
        previousMillis += job_period;
        Serial.println(energy);
    }
  }

     // control LEDs
    if (energy > 90) {
      digitalWrite (ledhouse, HIGH);
    }
    if (energy < 90) {
      digitalWrite (ledhouse, LOW);
    }
    if (energy > 95) {
      digitalWrite (ledwater, HIGH);
    }
    if (energy < 95) {
      digitalWrite (ledwater, LOW);
    }

    // control motor for windmills
    if (energy > 110) {
      digitalWrite (motorPin, HIGH);
      //Serial.println("motor is on");
    }

    else {
      digitalWrite (motorPin, LOW);
      //Serial.println("motor is off");
    }

   // Vap: switch off vap if energy > 20
    if (energy > 85 & vap_switch ==0) {
      //myservo.attach(9);
      myservo.write(180);
      //myservo.detach();
      vap_switch = 1;
    }

   // Vap: switch on vap if energy <= 20
    if (energy < 85 & vap_switch ==1) {
      //myservo.attach(9);
      myservo.write(49);
      //Serial.println("servo is on");
      vap_switch = 0;
      //myservo.detach();
    }

  //Neopixel:sunrise
  //start out off, fade up to first color orange (255, 80, 0)
  if (energy >= 105){
  for (int i = 0; i < faderate; i++)
  {
    int r = map(i, 0, faderate, 0, 255);//fade up the value of red
    int g = map(i, 0, faderate, 0, 80); //fade up the value of green
    colorWipe (strip1.Color(r, g, 0),0);
    colorWipe (strip2.Color(r, g, 0),0);
    strip1.show();
    strip2.show();
    delay (wait);
  }

  //fade from orange to yellow (255, 255, 0)
  for (int i = 0; i < faderate; i++)
  {
    int g = map(i, 0, faderate, 80, 255); //fade up the value of green
    colorWipe (strip1.Color(255, g, 0),0);
    strip1.show();
    colorWipe (strip2.Color(255, g, 0),0);
    strip2.show();
    delay (wait);
    strip1.Color(255,255,0);
    strip2.Color(255,255,0);
  }
  }

   //Neopixel:rainbow
    if (energy >= 115) {
    colorWipe(strip1.Color(255, 0, 0), 50); // Red
    colorWipe(strip1.Color(0, 255, 0), 50); // Green
    colorWipe(strip1.Color(0, 0, 255), 50); // Blue
    rainbow(16);
    rainbowCycle(16);

    colorWipe(strip2.Color(255, 0, 0), 50); // Red
    colorWipe(strip2.Color(0, 255, 0), 50); // Green
    colorWipe(strip2.Color(0, 0, 255), 50); // Blue
    rainbow(24);
    rainbowCycle(24);
    }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip1.numPixels(); i++) {
      strip1.setPixelColor(i, c);
      strip1.show();
  }
  for(uint16_t i=0; i<strip2.numPixels(); i++) {
      strip2.setPixelColor(i, c);
      strip2.show();
  }
      //delay(wait);
  }
 
void rainbow(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256; j++) {
    for(i=0; i<strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip1.show();
    for(i=0; i<strip2.numPixels(); i++) {
      strip2.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip2.show();
    //delay(wait);
  }
}
 
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel(((i * 256 / strip1.numPixels()) + j) & 255));
    }
    strip1.show();
    for(i=0; i< strip2.numPixels(); i++) {
    strip2.setPixelColor(i, Wheel(((i * 256 / strip2.numPixels()) + j) & 255));
    }
    strip2.show();
    //delay(wait);
  }
}
 
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip1.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
   return strip2.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip1.Color(255 - WheelPos * 3, 0, WheelPos * 3);
   return strip2.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip1.Color(0, WheelPos * 3, 255 - WheelPos * 3);
   return strip2.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
