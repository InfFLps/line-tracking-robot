/**
 * @param of sensor1: when 0 then black, if not then white
 * @param of sensor2: opposite of sensor1
 *
 */

#define AIN1 13
#define AIN2 14
#define BIN1 32
#define BIN2 33
#define PWMA 25
#define PWMB 26

const uint32_t PWM_FREQ = 20000;
const uint8_t  PWM_RES  = 8;

int sensor1 = 23; // Right
int sensor2 = 27;

void motor(uint8_t ain1State, uint8_t ain2State, uint8_t bin1State, uint8_t bin2State, uint8_t leftSpeed, uint8_t rightSpeed) {
  digitalWrite(AIN1, ain1State);
  digitalWrite(AIN2, ain2State);
  digitalWrite(BIN1, bin1State);
  digitalWrite(BIN2, bin2State);

  ledcWrite(PWMA, leftSpeed);
  ledcWrite(PWMB, rightSpeed);
}

void goStraight(int pwma, int pwmb) { 
  motor(1, 0, 0, 1, pwma, pwmb); 
}
void turnLeft(int baseSpeed) {
  motor(1, 0, 0, 1, baseSpeed / 4, baseSpeed);
}
void turnRight(int baseSpeed) {
  motor(1, 0, 0, 1, baseSpeed, baseSpeed / 4);
}
void goBack(int pwma, int pwmb) {
   motor(0, 1, 1, 0, pwma, pwmb); 
}
void stopMotor()  { 
  motor(0, 0, 0, 0, 0, 0); 
}

void setup() {
  Serial.begin(115200);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  ledcAttach(PWMA, PWM_FREQ, PWM_RES);
  ledcAttach(PWMB, PWM_FREQ, PWM_RES);

  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  stopMotor();
}

void loop() {
  int sval1 = digitalRead(sensor1);
  int sval2 = digitalRead(sensor2);

  if(sval1 == 0 && sval2 == 0) {
    goStraight(200, 200);
  } else if(sval1 == 1) {
    turnLeft(200);
  } else if(sval2 == 1) {
    turnRight(200);
  } else {
    stopMotor();
  }

  Serial.println("sensorval: ");
  Serial.println(sval1);
  Serial.println("sval2: ");
  Serial.println(sval2);
  delay(500);

}
