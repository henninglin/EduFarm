#include <Wire.h>
 
#define greenLED 12
#define yellowLED 11
#define brownLED 9
#define orangeLED 10
#define attachmentGreen A3
#define attachmentRed A2
#define buzzerPin A1
 
int c = 0;
boolean beepSucceed = false;
boolean beepFailed = false;
 
//L293D
//Motor A
const int enA = 6; // Pin 7 of L293
const int motorPin1  = 8;  // Pin 1 of L293
const int motorPin2  = 7;  // Pin 2 of L293
//Motor B
const int enB = 3; // Pin 9 of L293
const int motorPin3  = 2; // Pin  10 of L293
const int motorPin4  = 4;  // Pin  15 of L293
 
void setup() {
  Wire.begin();        // join i2c bus
  Serial.begin(9600);  // start serial for output
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(brownLED, OUTPUT);
  pinMode(orangeLED, OUTPUT);
  pinMode(attachmentGreen, OUTPUT);
  pinMode(attachmentRed, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}
 
void loop() { 
  Wire.requestFrom(8, 1);    // request 1 byte from slave device at address 8
 
  while (Wire.available()) { // slave may send less than requested
    c = Wire.read(); // receive a byte as int
    Serial.print(c);         // print the int
  }
  // turns on green LED on top of tractor, rest of LEDs turns off     
  if (c == 1) {           
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(brownLED, LOW);
    digitalWrite(orangeLED, LOW);
  }  
  // turns on yellow LED on top of tractor, rest of LEDs turns off  
  else if (c == 2) { 
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(brownLED, LOW);
    digitalWrite(orangeLED, LOW);
  } 
  // turns on orange LED on top of tractor, rest of LEDs turns off  
  else if (c == 3) {
    digitalWrite(orangeLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(brownLED, LOW);
  }  
  // turns on brown LED on top of tractor, rest of LEDs turns off  
  else if (c == 4) { 
    digitalWrite(brownLED, HIGH);
    digitalWrite(orangeLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
  } 
  // turns on green LED on top of tractor and green LED at the back of tractor, rest of LEDs turns off
  else if (c == 5) { 
    digitalWrite(attachmentGreen, HIGH);
    digitalWrite(attachmentRed, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(orangeLED, LOW);
    digitalWrite(brownLED, LOW);
  } 
  // turns on yellow LED on top of tractor and green LED at the back of tractor, rest of LEDs turns off
  else if (c == 6) {
    digitalWrite(attachmentGreen, HIGH);
    digitalWrite(attachmentRed, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(orangeLED, LOW);
    digitalWrite(brownLED, LOW);
  } 
  // turns on orange LED on top of tractor and green LED at the back of tractor, rest of LEDs turns off
  else if (c == 7) {
    digitalWrite(attachmentGreen, HIGH);
    digitalWrite(attachmentRed, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(orangeLED, HIGH);
    digitalWrite(brownLED, LOW);
  } 
  // turns on brown LED on top of tractor and green LED at the back of tractor, rest of LEDs turns off
  else if (c == 8) {
    digitalWrite(attachmentGreen, HIGH);
    digitalWrite(attachmentRed, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(orangeLED, LOW);
    digitalWrite(brownLED, HIGH);
  }
  // turns on red LED at the back of tractor, rest of LEDs turns off
  else {
    digitalWrite(attachmentGreen, LOW);
    digitalWrite(attachmentRed, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(orangeLED, LOW);
    digitalWrite(brownLED, LOW);
  }

 // makes the tractor drive forward at normal speed if int c is read as 5,6,7 or 8
  if (c == 5 || c == 6 || c == 7 || c == 8) {
    normalSpeed();
    forward();
    // buzzer beeping in a successful tone if boolean beepSuceed is false
    if(beepSucceed == false){
      buzzerSuccess();
      beepSucceed = true;
      beepFailed = false;
    }
  } 
  // makes tractor turn right if c is read as 9
  else if (c == 9) {
    rightTurn();
  } 
  // makes tractor turn left if c is read as 10
  else if (c == 10) {
    leftTurn();
  } 
  // makes tractor stop driving if c is none of the above values
  else {
    stopDriving();
    // buzzer beeping in a unsuccessful tone if boolean beepFailed is false
    if(beepFailed == false){
      buzzerFail();
      beepFailed = true;
      beepSucceed = false;
    }
  }
}

// turns one motorPin on, on both DC motors to spin the wheels in a forward direction
void forward() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}
// turns one motorPin on, on both DC motors but at different speeds to make the tractor turn left 
void leftTurn() {
  analogWrite(enA, 247);
  analogWrite(enB, 70);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}
// turns ono motorPin on, on both DC motors but at different speeds to make the tractor turn right 
void rightTurn() {
  analogWrite(enA, 73);
  analogWrite(enB, 255);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}
// turns off both DC motors 
void stopDriving() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}
// sets each DC motor to a specific speed with motor driver two enable pins to make them same speed
void normalSpeed() {
  analogWrite(enA, 247);                      
  analogWrite(enB, 255);
}

// makes buzzer sound in a successful tone with three different tones activated after each other 
// ending with noTone to stop the buzzer sound
void buzzerSuccess() {
  tone(buzzerPin, 523, 125);
  delay(100);
  tone(buzzerPin, 587, 125);
  delay(100);
  tone(buzzerPin, 659, 125);
  delay(100);
  noTone(buzzerPin);
}
// makes buzzer sound in a unsuccessful tone with four different tones activated after each other 
// ending with noTone to stop the buzzer sound
void buzzerFail() {
  tone(buzzerPin, 523, 125);
  delay(100);
  tone(buzzerPin, 440, 125);
  delay(100);
  tone(buzzerPin, 349, 125);
  delay(100);
  tone(buzzerPin, 262, 125);
  delay(100);
  noTone(buzzerPin);
}
