#include <SPI.h>
#include <Wire.h>

#define S0 9
#define S1 8
#define S2 11
#define S3 12
#define sensorOut 10

int frequency = 0;
int color = 0;

void setup() {
  Wire.begin(8);      // join i2c bus
  Wire.onRequest(requestEvent);
  Serial.begin(9600); // initialize serial communications with the PC
  while (!Serial); // do nothing if no serial port is opened 
  SPI.begin(); // init SPI bus

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
}

void loop() {
  requestEvent();
  delay(500);
}



void requestEvent() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= "); //printing name
  Serial.print(frequency); //printing red color frequency
  Serial.print("  ");
  delay(50);

  // Setting green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing green color frequency
  Serial.print("  ");
  delay(50);

  // Setting blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing blue color frequency
  Serial.println("  ");
  delay(50);

  int sensorValue = analogRead(A3);
  float voltage = sensorValue * (5.0 / 1024.0);

  float I = voltage / 1000;
  float VRx = 5 - voltage;
  float Rx = VRx / I;
  Rx = (5 - voltage) / I;

  // print out the value read:
  Serial.print("Resistance:");
  Serial.print(Rx);
  Serial.println(" Ohms");

    // sets color to 1 if green and blue frequency is within interval
/*  if (G<400 & G>351 & B<400 & B>351) {
    color = 1; //Brown
    // sets color to 5 if color is 1 and resistor value Rx is between interval 
    if (color == 1 && Rx > 600 && Rx < 1500) {
      color = 5; // Brown && Attachment greenLED
    }
  }*/

  // sets color to 2 if green and blue frequency is within interval 
  if (G<8000 & G>351 & B<8000 & B>351) {
    color = 2; // Green
    // sets color to 6 if color is 2 and resistor value Rx is between interval 
    if (color == 2 && Rx > 4000 && Rx < 110000) {
      color = 6; // Green && Attachment greenLED
    }
  }
  // sets color to 3 if green and blue frequency is within interval
  if (G<350 & G>1 & B<350 & B>1) {
    color = 3; // Yellow
    // sets color to 7 if color is 3 and resistor value Rx is between interval 
    if (color == 3 && Rx > 1 && Rx < 3999) {
      color = 7; // Yellow && Attachment greenLED
    }
  }
    // sets color to 4 if green and blue frequency is within interval
/*  if (G<310 & G> & B<209 & B>181) {
    color = 4; // Orange
    // sets color to 8 if color is 4 and resistor value Rx is between interval 
    if (color == 4 && Rx > 200 && Rx < 500) {
      color = 8; // Orange && Attachment greenLED
    }
  }
  // sets color to 9 if green and blue frequency is within interval
  if (G<23 & G>20 & B<23 & B>20) {
    color = 9; // Red
  }
  // sets color to 10 if green and blue frequency is within interval
  if (G<28 & G>24 & B<28 & B>24) {
    color = 10; // Blue
  }
*/
  Wire.write(color); // sends color as a message of 1 byte to master
  color = 0; // resets color to 0
}
