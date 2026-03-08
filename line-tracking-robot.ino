#define AIN1 13
#define AIN2 14
#define BIN1 32
#define BIN2 33
#define PWMA 25
#define PWMB 26

const uint32_t PWM_FREQ = 20000;
const uint8_t  PWM_RES  = 8;

int sensor1 = 23; // Right
int sensor2 = 21; // Middle
int sensor3 = 27; // Left

float Kp = 40;
float Ki = 0;
float Kd = 20;

float error = 0;
float lastError = 0;
float integral = 0;

const int leftWeight = -1;
const int middleWeight = 0;
const int rightWeight = 1;

int baseSpeed = 150;

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

void stopMotor() { 
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
  pinMode(sensor3, INPUT);

  stopMotor();
}

void loop() {

  int sval1 = digitalRead(sensor1); // Right
  int sval2 = digitalRead(sensor2); // Middle
  int sval3 = digitalRead(sensor3); // Left

  if (sval3 == 1 && sval2 == 0 && sval1 == 0) error = leftWeight;
  else if (sval3 == 1 && sval2 == 1 && sval1 == 0) error = -0.5;
  else if (sval3 == 0 && sval2 == 1 && sval1 == 0) error = middleWeight;
  else if (sval3 == 0 && sval2 == 1 && sval1 == 1) error = 0.5;
  else if (sval3 == 0 && sval2 == 0 && sval1 == 1) error = rightWeight;
  else error = lastError;

  integral += error;
  float derivative = error - lastError;

  float correction = Kp * error + Ki * integral + Kd * derivative;

  lastError = error;

  int leftSpeed  = baseSpeed + correction;
  int rightSpeed = baseSpeed - correction;

  leftSpeed  = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  goStraight(leftSpeed, rightSpeed);

  Serial.print("L:");
  Serial.print(sval3);

  Serial.print(" M:");
  Serial.print(sval2);

  Serial.print(" R:");
  Serial.print(sval1);

  Serial.print(" | Error:");
  Serial.print(error);

  Serial.print(" | PID:");
  Serial.print(correction);

  Serial.print(" | LS:");
  Serial.print(leftSpeed);

  Serial.print(" RS:");
  Serial.println(rightSpeed);

  delay(50);
}
