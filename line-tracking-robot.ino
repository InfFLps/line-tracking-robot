/**
  * ?notice Variables with "const" aren't meant to be changed
  */

#define AIN1 13 // left motor
#define AIN2 14 // left motor

#define BIN1 32 // right motor
#define BIN2 33 // right motor

#define PWMA 25 // left motor
#define PWMB 26 // right motor

#include "QTRSensors.h" // includes the library that handles the sensors
QTRSensors qtr; // initializes the library as vaiable qtr

uint8_t sensorPins[] = {
  27 /*sensor 1*/,
  23 /*sensor 2*/,
  22 /*sensor 3*/,
  18 /*sensor 4*/,
  19 /*sensor 5*/,
  21 /*sensor 6*/,
  16 /*sensor 7*/,
  17 /*sensor 8*/
  }; const uint16_t sensorValues[]; const uint8_t sensorCount = 8;
const uint16_t threshold = 1000;

/**
  * void motor(){} Manages the motor
  * @param left handles the left motor speed
  * @param right handles the right motor speed
  */
void motor(int left, int right) {
  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW); digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);
  digitalWrite(PWMA, left); digitalWrite(PWMB, right);
} void straight() {motor(200, 200);}
void left() {motor(20, 200);} void right() {motor(200, 20);} void stop() {motor(0, 0);}

void qtrManager(uint8_t &left, uint8_t &middle, uint8_t &right) {
  qtr.read(sensorValues);
  uint8_t sensor[8];
  for(int i = 0; i < 8; i++) {
    sensor[i] = (sensorValues[i] > threshold) ? 1 : 0;
  }

  left = sensor[0] | sensor[1];
  middle = sensor[2] | sensor[3] | sensor[4] | sensor[5];
  right = sensor[6] | sensor[7];
}
void setup() {
  qtr.setTypeRC(); // tells the library that the sensor is RC, not an analog
  qtr.setSensorPins(sensorPins, sensorCount) // this function automatically handles all timing and calibration
  for(int i = 0; i < 400; i++) {
    qtr.calibrate();
    delay(5);
  }
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  stop(); // stops the motor at first initialization (for debugging porposes)
}

void loop() {
  uint8_t left, middle, right;
  qtrManager(left, middle, right);
  if(left == 0 && middle == 1 && right == 0) {
    straight();
  } else if(left == 1) {
    right();
  } else if(right == 1) {
    left();
  } else {
    stop();
  }
}
