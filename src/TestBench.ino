#include <Wire.h>

const int IN1 = 9; // Orange wire
const int IN2 = 6; // Green wire
const int D1 = 11; // Red wire
const int D2 = 10; // Gray wire
const int EN = 8; // Yellow wire
int count = 0;
int message; 

// 4 other wires: Orange-Red= Vin, Black-Blue = Ground, White = Out2, Brown = Out1
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

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


}

void loop() {
  // put your main code here, to run repeatedly

  if(Serial.available() > 0){
    message = Serial.read();

    if(message == 'f'){ //'f' car moves forward
      digitalWrite(IN1, 1);
      digitalWrite(IN2, 0);
      digitalWrite(EN, 1);
      Serial.println("Forward"); //Prints "Forward"
    }

    if(message == 'r'){ //'r' car moves reverse
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 1);
      digitalWrite(EN,1);
      Serial.println("Reverse"); //Prints "Reverse"
    }

    if(message == 's'){ //'s' car stops
      digitalWrite(EN,0);
      Serial.println("Stop"); //Prints "Stop"
    }
  }



}
