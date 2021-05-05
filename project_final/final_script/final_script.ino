#include <IRremote.h>
#include <IRremoteInt.h>

// Constants leds
const byte pinRed = 8;
//const byte pinGreen = 12;
const byte pinBlue = 4;
const byte pinTest = 13;
const byte pinReceptor = 2;

// Constants (PWM) wheels
const byte AIB = 6;
const byte BIA = 9;
const byte AIA = 10;
const byte BIB = 11;

// Constants Sensor
const byte pinShoot = 7;
const int pinEcho = 12;

//
const byte distanceLimit = 10;
long timePulse;
float dstMeasure; // Distance

void setup() {
  // Enabled data received and transfer by Serial Port
  Serial.begin(9600);
  // init to start receipr signals
  IrReceiver.begin(pinReceptor, true);

  //Config led's pins
  pinMode(pinRed, OUTPUT);
  //pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);

  //Config wheels' pins
  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);

  pinMode(pinTest, OUTPUT);

  //Config sensor's pins
  pinMode(pinShoot, OUTPUT);
  //pinMode(pinEcho, INPUT);

  // Initialize led RGB
  analogWrite(pinRed, 0);
  //analogWrite(pinGreen, 0);
  analogWrite(pinBlue, 0);

  //shutdown led
  digitalWrite(pinTest, LOW);

  //shutdown wheels
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);

  //shutdown sensor
  digitalWrite(pinShoot, LOW);

  sayHello();
}

void loop() {

  if (IrReceiver.decode()) {
    int pressValue = IrReceiver.decodedIRData.command;

    switch (pressValue) {
      case 24: //Button 2
        moveForwardAction();
        break;
      case 8: // Button 4
        moveTurnLeftAction();
        break;
      case 28: // Button 5
        turnOnStopLedAction();
        break;
      case 90: // Button 6
        moveTurnRightAction();
        break;
      case 82: // Button 8
        moveReverseAction();
        break;
      default:
        moveStop();
        shutDownLed();
        break;
    }

    delay(10);
    // Receive the next value
    IrReceiver.resume();
  } else { // This else will stop the wheels when the control does not send a signal.
    delay(200);
    moveStop();
    shutDownLed();
  }
}

/********************************/
/*********** ACTIONS ************/
/********************************/

void moveForwardAction() {
  shutDownLed();
  if (calculateDistance() > distanceLimit) {
    genericMove(255, 0, 255, 0);
  } else {
    moveStop();
    turnOnStopLed();
    shutDownLed();
  }
}

void moveReverseAction() {
  turnOnReverseLed();
  genericMove(0, 255, 0, 255);
}

void moveTurnLeftAction() {
  shutDownLed();
  genericMove(255, 0, 0 , 255);
  delay(250);
  moveStop();
}

void moveTurnRightAction() {
  shutDownLed();
  genericMove(0, 255, 255, 0);
  delay(250);
  moveStop();
}

void moveStop() {
  genericMove(255, 255, 255, 255);
}

void turnOnStopLedAction() {
  moveStop();
  turnOnStopLed();
  shutDownLed();
}


/********************************/
/*********** SENSORS ************/
/********************************/

float calculateDistance() {
  digitalWrite(pinShoot, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinShoot, LOW);
  timePulse = pulseIn(pinEcho, HIGH);
  /*
     Formule to calculate the distance to an object and as a result you will get a FLOAT value.
     340 m/s = 0.034 cm/us; 340 m/s is the speed of sound. In this case it could be  0.034 / 2 = 0.017
  */
  return (0.017 * timePulse);
}


/********************************/
/*********** LEDS ***************/
/********************************/

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
  //digitalWrite(pinGreen, LOW);
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
  //digitalWrite(pinGreen, HIGH);
  digitalWrite(pinBlue, HIGH);
}

void shutDownLed() {
  digitalWrite(pinRed, LOW);
  //digitalWrite(pinGreen, LOW);
  digitalWrite(pinBlue, LOW);
}

/********************************/
/*********** MOTORS *************/
/********************************/

void genericMove(int aiaValue, int aibValue, int biaValue, int bibValue) {
  analogWrite(AIA, aiaValue);
  analogWrite(AIB, aibValue);
  analogWrite(BIA, biaValue);
  analogWrite(BIB, bibValue);
}
