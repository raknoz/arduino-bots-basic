// Constants
// pins PWM
const byte AIA = 3;
const byte AIB = 11;
const byte BIA = 9;
const byte BIB = 10;

const byte ledTest = 13;

void setup() {

  //Setup outputs
  pinMode(ledTest, OUTPUT);
  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);

  //shutdown exits
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);

  digitalWrite(ledTest, LOW);
}

void loop() {
  ledSignal(1);
  moveForward();
  delay(1500);
  moveStop();

  ledSignal(2);
  moveTurnRight();
  delay(1500);
  moveStop();

  ledSignal(3);
  moveTurnLeft();
  delay(1500);
  moveStop();

  ledSignal(4);
  moveReverse();
  delay(1500);
  moveStop();
}

//Private methods

void moveForward() {
  analogWrite(AIA, 255);
  analogWrite(AIB, 0);
  analogWrite(BIA, 255);
  analogWrite(BIB, 0);
}

void moveReverse() {
  analogWrite(AIA, 0);
  analogWrite(AIB, 255);
  analogWrite(BIA, 0);
  analogWrite(BIB, 255);
}

void moveTurnRight() {
  analogWrite(AIA, 255);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 255);
}

void moveTurnLeft() {
  analogWrite(AIA, 0);
  analogWrite(AIB, 255);
  analogWrite(BIA, 255);
  analogWrite(BIB, 0);
}

void moveStop() {
  analogWrite(AIA, 255);
  analogWrite(AIB, 255);
  analogWrite(BIA, 255);
  analogWrite(BIB, 255);
  delay(500);
}

void ledSignal(int times) {
  for (int t = 0; t < times; t++) {
    digitalWrite(ledTest, HIGH);
    delay(200);
    digitalWrite(ledTest, LOW);
    delay(200);
  }
}