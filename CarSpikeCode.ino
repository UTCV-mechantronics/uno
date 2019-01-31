#include <Wire.h>

const int IN1 = 9; // Orange wire
const int IN2 = 6; // Green wire
const int D1 = 11; // Red wire
const int D2 = 10; // Gray wire
const int EN = 8; // Yellow wire
int spikeCount = 0;
double circumference = 47.88;
int message;
int magnetStrength;
int timeStart;
int timeEnd;
int timeElapsed;
bool resets = true;
double speedAvg;
unsigned long previousMillis = 0;
bool carRunning = false;
int count = 0;
// 4 other wires: Orange-Red= Vin, Black-Blue = Ground, White = Out2, Brown = Out1
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(A5, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(EN, OUTPUT);

  digitalWrite(EN,0); // Settings for intial conditions -> stationary car
  digitalWrite(D2,1);
  digitalWrite(D1,0);
  digitalWrite(IN1,1);
  digitalWrite(IN2,0);

  {

  }


}


void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available() > 0 && !carRunning){
    message = Serial.read();
    
    if(message == 102){ //'f' car moves forward
      digitalWrite(IN1, 1);
      digitalWrite(IN2, 0);
      digitalWrite(EN, 1);
      Serial.println("Start");
      carRunning = true;
      count = 0;
    }  
  }
    if(carRunning == true){

      
      unsigned long currentMillis = millis();
      magnetStrength = analogRead(A0);
      Serial.println(magnetStrength);
      
      if (magnetStrength > 300 && resets) {
        spikeCount = spikeCount + 1;
        resets = false;
      }
      else if (magnetStrength < 200 && !resets) {
        resets = true;
      }
  
      if (currentMillis - previousMillis >= 500) { //Will enter If statement if time > 0.5s
         count = count + 1;
         //Save last time we printed
         previousMillis = currentMillis;
         //voltageAvg = INSERT CODE TO FIND AVG VOLTAGE
         speedAvg = (circumference * (spikeCount/4)) / currentMillis; 
         //Serial.print(speedAvg);
         //Serial.print(", ");
         //Serial.println(2);
      }
      if(count == -1){
        carRunning = false;
        Serial.println("done");
        digitalWrite(EN, 0);
      }
    }
}
      
      
