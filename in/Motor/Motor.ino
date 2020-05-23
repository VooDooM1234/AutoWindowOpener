#define IN1 7 //GPIO 14
#define IN2 5 //GPIO 12
#define IN3 6 //GPIO 13
#define IN4 4 //GPIO 15

const int NBSTEPS = 4096;
const int STEPTIME = 1000;
int Step = 0;
boolean Clockwise = true;

int arrayDefault[4] = {LOW, LOW, LOW, LOW};

int stepsMatrix[8][4] = {
  {LOW, LOW, LOW, HIGH},
  {LOW, LOW, HIGH, HIGH},
  {LOW, LOW, HIGH, LOW},
  {LOW, HIGH, HIGH, LOW},
  {LOW, HIGH, LOW, LOW},
  {HIGH, HIGH, LOW, LOW},
  {HIGH, LOW, LOW, LOW},
  {HIGH, LOW, LOW, HIGH},
};

unsigned long lastTime = 0L;
unsigned int count = 0L;

void writeStep(int outArray[4]);
void stepper();
void setDirection();

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  unsigned long currentMicros;
  int stepsLeft = NBSTEPS;
  count = 0;
  lastTime = micros();
  while (stepsLeft > 0) {
    currentMicros = micros();
    if (currentMicros - lastTime >= STEPTIME) {
      stepper();
      count += micros() - lastTime;
      lastTime = micros();
      stepsLeft--;
    }
    delay(1);
  }
  Serial.println(count);
  Serial.println("Wait...!");
  delay(2000);
  Clockwise = !Clockwise;
  stepsLeft = NBSTEPS;
}

void writeStep(int outArray[4]) {
  digitalWrite(IN1, outArray[0]);
  digitalWrite(IN2, outArray[1]);
  digitalWrite(IN3, outArray[2]);
  digitalWrite(IN4, outArray[3]);
}

void stepper() {
  if ((Step >= 0) && (Step < 8)) {
    writeStep(stepsMatrix[Step]);
  } else {
    writeStep(arrayDefault);
  }
  setDirection();
}

void setDirection() {
  (Clockwise == true) ? (Step++) : (Step--);

  if (Step > 7) {
    Step = 0;
  } else if (Step < 0) {
    Step = 7;
  }
}
