unsigned long time;
float Voltage_House = 0.0;
float Voltage_Tree = 0.0;
float Voltage_Ore = 0.0;
float Voltage_Coal = 0.0;
int s0 = 1;
int s1 = 2;
int s2 = 3;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);     
}

// Make sure to range Voltage between 4:30-4:32 // 

void loop() {
 // put your main code here, to run repeatedly:

 time = millis();
 
 // Registering tree token // 
 
Voltage_Tree = analogRead(A0);
Voltage_Tree = (Voltage_Tree * 5.0) / 1024.0;
Serial.println(Voltage_Tree);

 // Resgitering house token //
  
 Voltage_House = analogRead(A1);
 Voltage_House = (Voltage_House * 5.0) / 1024.0;
 Serial.println(Voltage_House);

 // Resgitering ore token //

 // Resgitering house token //
}
