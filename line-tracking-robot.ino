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

uint8_t sensorPins[] = {27, 23, 22, 18, 19, 21, 16, 17};
const uint8_t sensorCount = 8;
uint16_t sensorValues[sensorCount];

void motor(uint8_t leftSpeed, uint8_t rightSpeed) {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);

  ledcWrite(PWMA, leftSpeed);
  ledcWrite(PWMB, rightSpeed);
}

void moveStart() { for(int i = 0; i <= 255; i++) {motor(i, i); delay(10);}}
void goStraight() { motor(255, 255); }
void turnLeft()   { motor(80, 255);  }
void turnRight()  { motor(255, 80);  }
void stopMotor()  { motor(0, 0);     }

void qtrManager(uint8_t &l, uint8_t &m, uint8_t &r) {
  qtr.read(sensorValues);

  uint8_t s[8];

  for (int i = 0; i < 8; i++) {
    uint16_t minV = qtr.calibrationOn.minimum[i];
    uint16_t maxV = qtr.calibrationOn.maximum[i];
    uint16_t th   = (minV + maxV) / 2;

    s[i] = (sensorValues[i] > th) ? 1 : 0;
  }

  l = s[0] | s[1];
  m = s[2] | s[3] | s[4] | s[5];
  r = s[6] | s[7];
}

void setup() {
  Serial.begin(115200);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  ledcAttach(PWMA, PWM_FREQ, PWM_RES);
  ledcAttach(PWMB, PWM_FREQ, PWM_RES);

  qtr.setTypeRC();
  qtr.setSensorPins(sensorPins, sensorCount);

  for (int i = 0; i < 400; i++) {
    qtr.calibrate();
    delay(5);
  }

  stopMotor();
}

void loop() {
  /*uint8_t l, m, r;
  qtrManager(l, m, r);

  // Debug sensor values
  for (int i = 0; i < sensorCount; i++) {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();

  if (l == 0 && m == 1 && r == 0) {
    goStraight();
  } else if (l == 1) {
    turnRight();
  } else if (r == 1) {
    turnLeft();
  } else {
    stopMotor();
  }

  delay(20);*/
  moveStart();
  goStraight();
  delay(1500);
  turnRight();
  delay(1500);
  turnLeft();
  delay(1500);
  stopMotor();
  delay(1500);
  }
