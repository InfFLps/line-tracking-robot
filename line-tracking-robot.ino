#include <QTRSensors.h>

#define AIN1 13
#define AIN2 14
#define BIN1 32
#define BIN2 33
#define PWMA 25
#define PWMB 26

const uint32_t PWM_FREQ = 20000;
const uint8_t  PWM_RES  = 8;

QTRSensors qtr;
const uint8_t NUM_SENSORS = 2;
uint16_t sensorValues[NUM_SENSORS];

const uint16_t thresholds[NUM_SENSORS] = {1000, 950};

void motor(uint8_t leftSpeed, uint8_t rightSpeed) {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);

  ledcWrite(PWMA, leftSpeed);
  ledcWrite(PWMB, rightSpeed);
}

void goStraight() { motor(255,255); }
void turnLeft() { motor(80,255); }
void turnRight() { motor(255,80); }
void stopMotor() { motor(0,0); }

void setup() {
  Serial.begin(115200);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  ledcAttach(PWMA, PWM_FREQ, PWM_RES);
  ledcAttach(PWMB, PWM_FREQ, PWM_RES);

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){34, 35}, NUM_SENSORS);

  stopMotor();
}

void loop() {
  qtr.read(sensorValues);

  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print("S"); Serial.print(i); Serial.print(": ");
    if(sensorValues[i] < thresholds[i]) Serial.print("BLACK\t");
    else Serial.print("WHITE\t");
  }
  Serial.println();

  if(sensorValues[0] < thresholds[0] && sensorValues[1] < thresholds[1]) {
    goStraight();
  } else {
    stopMotor();
  }

  delay(50);
}
