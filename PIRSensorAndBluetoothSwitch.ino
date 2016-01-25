char val; // variable to receive data from the serial port

bool isOn;

int pinS = 8; // servo
int pinT = 9; // transistor

int calibrationTime = 20; // time for PIR sensors to calibrate
int pirPin = 13; // PIR sensor
int ledPin = 10; // led

#include <Servo.h>
Servo myservo;

void setup() {
  myservo.attach(pinS);
  pinMode(pinT, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);
  
  Serial.begin(9600);       // start serial communication at 9600bps

  //give the sensor some time to calibrate
  for(int i = 0; i < calibrationTime; i++){
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
  
  lightsOn();
  lightsOff();
}

void loop() {

  // Read input from the bluetooth device
  if( Serial.available() )       // if data is available to read
  {
    val = Serial.read();         // read it and store it in 'val'
  }

  // Read input from the PIR sensor;
  if (digitalRead(pirPin) == HIGH){
    isOn = !isOn;
    if (isOn){
      lightsOn();
    }
    else {
      lightsOff();   
    }
    delay(2000);
  }
  
  if ( val == '1' ){
    lightsOn();
    val = ' ';
  } else if ( val == '0' ) {
    lightsOff();
    val = ' ';
  }
}

void lightsOn() {
  digitalWrite(pinT, HIGH);
  myservo.write(7);              // tell servo to go to position in variable 'pos'
  Serial.println("Light is on.");
  isOn = 1; 
  delay(500);
  digitalWrite(pinT, LOW);
}

void lightsOff() {
    digitalWrite(pinT, HIGH);
    myservo.write(30);              // tell servo to go to position in variable 'pos'
    Serial.println("Light is off.");
    isOn = 0;
    delay(500);
    digitalWrite(pinT, LOW);
}
