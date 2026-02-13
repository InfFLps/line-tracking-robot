#define AIN1 13
#define AIN2 14
#define BIN1 32
#define BIN2 33
#define PWMA 25
#define PWMB 26

const uint32_t PWM_FREQ = 20000;
const uint8_t  PWM_RES  = 8;

const int SENSOR_PINS[] = {35, 34, 15, 12, 2, 4};
const int NUM_SENSOR_PIN = sizeof(SENSOR_PINS) / sizeof(SENSOR_PINS[0]);

int sensorThreshold[NUM_SENSOR_PIN];

void motor(uint8_t leftSpeed, uint8_t rightSpeed) {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);

  ledcWrite(PWMA, leftSpeed);
  ledcWrite(PWMB, rightSpeed);
}

void goStraight() { motor(255,255); }
void turnLeft() { motor(80,255); }
void turnRight() { motor(255,80); }
void
void stopMotor() { motor(0,0); }

void calibrateSensorsWithMovement(int durationMs = 5000, int intervalMs = 50) {
  int minValues[NUM_SENSOR_PIN];
  int maxValues[NUM_SENSOR_PIN];

  for (int i = 0; i < NUM_SENSOR_PIN; i++) {
    minValues[i] = 4095;
    maxValues[i] = 0;
  }

  Serial.println("Start calibration: rotate robot over line");

  unsigned long startTime = millis();
  while (millis() - startTime < durationMs) {
    motor(150, 5;
    delay(intervalMs);

    for (int i = 0; i < NUM_SENSOR_PIN; i++) {
      int val = analogRead(SENSOR_PINS[i]);
      if (val < minValues[i]) minValues[i] = val;
      if (val > maxValues[i]) maxValues[i] = val;
    }
  }

  stopMotor();

  for (int i = 0; i < NUM_SENSOR_PIN; i++) {
    sensorThreshold[i] = (minValues[i] + maxValues[i]) / 2;
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" threshold = ");
    Serial.println(sensorThreshold[i]);
  }

  Serial.println("Calibration complete!");
}


void setup() {
  Serial.begin(115200);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  ledcAttach(PWMA, PWM_FREQ, PWM_RES);
  ledcAttach(PWMB, PWM_FREQ, PWM_RES);
  stopMotor();

  calibrateSensorsWithMovement();
}

void loop() {
  motor(100, 100);
  int SENSOR_VALUE[NUM_SENSOR_PIN];
  SENSOR_VALUE[0] = analogRead(SENSOR_PINS[0]);
  SENSOR_VALUE[1] = analogRead(SENSOR_PINS[1]);
  SENSOR_VALUE[2] = analogRead(SENSOR_PINS[2]);
  SENSOR_VALUE[3] = analogRead(SENSOR_PINS[3]);
  SENSOR_VALUE[4] = analogRead(SENSOR_PINS[4]);
  SENSOR_VALUE[5] = analogRead(SENSOR_PINS[5]);

  for (int i = 0; i < NUM_SENSOR_PIN; i++) {
    int detected = SENSOR_VALUE[i] < sensorThreshold[i] ? 1 : 0;
    Serial.print(SENSOR_VALUE[i]);
    Serial.print("(");
    Serial.print(detected);
    Serial.print(")\t");
  }
  Serial.println();
  delay(100);
}
