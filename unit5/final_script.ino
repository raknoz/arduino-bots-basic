#include <IRremote.h>
#include <IRremoteInt.h>

// Constants leds
const byte pinRed = 8;
const byte pinGreen = 12;
const byte pinBlue = 4;
const byte pinTest = 13;
const byte pinReceptor = 2;

// Constants (PWM) wheels
const byte AIB = 6;
const byte BIA = 9;
const byte AIA = 10;
const byte BIB = 11;

//
int irValue = 0; // variable to store the read value

void setup() {
  Serial.begin(9600);
  // init to start receipr signals
  IrReceiver.begin(pinReceptor, true);

  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);

  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);

  pinMode(pinTest, OUTPUT);

  analogWrite(pinRed, 0);
  analogWrite(pinGreen, 0);
  analogWrite(pinBlue, 0);

  digitalWrite(pinTest, LOW);

  //shutdown
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);

  sayHello();
}

void loop() {

  // Read signal of control
  irValue = digitalRead(pinReceptor);

  if (irValue = HIGH && IrReceiver.decode()) {
    int pressValue = IrReceiver.decodedIRData.command;
    Serial.println(pressValue);

    switch (pressValue) {
      case 24: //Button 2
        shutDownLed();
        moveForward();
        break;
      case 8: // Button 4
        shutDownLed();
        moveTurnLeft();
        delay(400);
        moveStop();
        break;
      case 28: // Button 5
        moveStop();
        turnOnStopLed();
        shutDownLed();
        break;
      case 90: // Button 6
        shutDownLed();
        moveTurnRight();
        delay(400);
        moveStop();
        break;
      case 82: // Button 8
        turnOnReverseLed();
        moveReverse();
        break;
      default:
        moveStop();
        shutDownLed();
        break;
    }

    delay(30);
    // Receive the next value
    IrReceiver.resume();
  } else {
    delay(200);
    moveStop();
    shutDownLed();
  }

}

void sayHello() {
  digitalWrite(pinTest, HIGH);
  delay(500);
  digitalWrite(pinTest, LOW);
  delay(500);
  digitalWrite(pinTest, HIGH);
  delay(500);
  digitalWrite(pinTest, LOW);
  delay(500);
  digitalWrite(pinTest, HIGH);
  delay(500);
  digitalWrite(pinTest, LOW);
  delay(500);
}

//Turn on red Led
void turnOnStopLed() {
  digitalWrite(pinGreen, LOW);
  digitalWrite(pinBlue, LOW);
  for (byte t = 0; t < 3; t++) {
    digitalWrite(pinRed, HIGH);
    delay(200);
    digitalWrite(pinRed, LOW);
    delay(200);
  }
}

//Turn on white Led
void turnOnReverseLed() {
  digitalWrite(pinRed, HIGH);
  digitalWrite(pinGreen, HIGH);
  digitalWrite(pinBlue, HIGH);
}

void shutDownLed() {
  digitalWrite(pinRed, LOW);
  digitalWrite(pinGreen, LOW);
  digitalWrite(pinBlue, LOW);
}

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

void moveTurnLeft() {
  analogWrite(AIA, 255);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 255);
}

void moveTurnRight() {
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
}
