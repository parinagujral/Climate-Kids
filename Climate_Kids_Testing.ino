#include <elapsedMillis.h>
unsigned long time;
unsigned int interval = 3000; // 180000 ms for 3 minutes // 
float Voltage_House = 0.0;
float Voltage_Tree = 0.0;
float Voltage_Ore = 0.0;
float Voltage_Coal = 0.0;
const int LED_Tree = 11;
const int LED_Ore = 12;
const int LED_House = 13;
const int LED_Coal = 14;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_Tree, OUTPUT);
  pinMode(LED_Ore, OUTPUT);
  pinMode(LED_Coal, OUTPUT);
  pinMode(LED_House, OUTPUT);
  Serial.begin(9600);     
}

void loop() {
 // put your main code here, to run repeatedly:

 time = millis();
 
 // Registering tree token // 
 
Voltage_Tree = analogRead(A0);
Voltage_Tree = (Voltage_Tree * 5.0) / 1024.0;
Serial.println(Voltage_Tree);

// Fade in and out when the tree is inserted, and blinks bright when the lumber is disposed //

if (Voltage_Tree = 2.203) 
{
    elapsedMillis timeElapsed;
    if (timeElapsed < interval)
    {
      int i = 0;
      for (int i = 0; i < 255; i++){ //if i is less than 255 then increase i with 1
      analogWrite(LED_Tree, i); //write the i value to pin 11
      delay(5); //wait 5 ms then do the for loop again
    }
      for (int i = 255; i > 0; i--){ //descrease i with 1
      analogWrite(LED_Tree, i);
      delay(5);
    }
    }
    
  else if (timeElapsed > interval)
  {
    digitalWrite(LED_Tree, HIGH);
    delay(100);
    digitalWrite(LED_Tree, LOW);
    delay(100);
  }
}

// Blink after 3 minutes to show tree is ready //

 // Registering house token //
  
Voltage_House = analogRead(A1);
Voltage_House = (Voltage_House * 5.0) / 1024.0;
Serial.println(Voltage_House);

 // Registering ore token //

Voltage_Ore = analogRead(A0);
Voltage_Ore = (Voltage_Ore * 5.0) / 1024.0;
Serial.println(Voltage_Ore);

// Fade in and out when the ore is inserted, and blinks bright when the ore is disposed //

if (Voltage_Ore = 1.116)
  {
    elapsedMillis timeElapsed;
    if (timeElapsed < interval)
    {
    int i = 0;
    for (int i = 0; i < 255; i++){ //if i is less than 255 then increase i with 1
      analogWrite(LED_Ore, i); //write the i value to pin 11
      delay(5); //wait 5 ms then do the for loop again
    }
    for (int i = 255; i > 0; i--){ //descrease i with 1
      analogWrite(LED_Ore, i);
      delay(5);
    }
    }

// Blink after 3 minutes to show ore is ready //

    else if (timeElapsed > interval)
    {
      digitalWrite(LED_Tree, HIGH);
      delay(100);
      digitalWrite(LED_Tree, LOW);
      delay(100);
    }
  }
 
 // Registering power plant token //
Voltage_Coal = analogRead(A0);
Voltage_Coal = (Voltage_Coal * 5.0) / 1024.0;
Serial.println(Voltage_Coal);

 // Turning on LED House //

if (Voltage_Coal = 3.676)
  {
    if (Voltage_House = 4.31)
   {
    digitalWrite(LED_House, HIGH);
   }
  }
 }
 
