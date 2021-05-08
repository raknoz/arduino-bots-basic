#include <IRremote.h>
#include <IRremoteInt.h>

// Constants leds
const int pinRed = A1;
const byte pinGB = A2;
const byte pinTest = 13;
const byte pinReceptor = 2;
const byte pinWhite = 5;

// Constants (PWM) wheels
const byte AIB = 6;
const byte BIA = 9;
const byte AIA = 10;
const byte BIB = 11;

// Constants Sensor
const byte pinShoot = 7;
const byte pinEcho = 12;

// Constants
const byte distanceLimit = 10;
long timePulse;
float dstMeasure; // Distance

void setup() {
  // Enabled data received and transfer by Serial Port
  Serial.begin(9600);
  // init to start receipt signals
  IrReceiver.begin(pinReceptor, true);

  //Config led pins
  pinMode(pinRed, OUTPUT);
  pinMode(pinGB, OUTPUT); // Green and Blue
  pinMode(pinWhite, OUTPUT);

  //Config wheels' pins
  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);

  pinMode(pinTest, OUTPUT);

  //Config sensor's pins
  pinMode(pinShoot, OUTPUT);

  // Initialize RGB led
  digitalWrite(pinRed, LOW);
  digitalWrite(pinGB, LOW);

  // Initialize white front leds
  analogWrite(pinRed, 0);

  // shutdown led
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
      case 12: // Button 1
        turnOnFrontLights();
        break;
      case 24: // Button 2
        moveForwardAction();
        break;
      case 94: // Button 3
        turnOffFrontLights();
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
  delay(170);
  moveStop();
}

void moveTurnRightAction() {
  shutDownLed();
  genericMove(0, 255, 255, 0);
  delay(170);
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
  /*
     Formule to calculate the distance to an object and as a result you will get a FLOAT value.
     340 m/s = 0.034 cm/us; 340 m/s is the speed of sound. In this case it could be  0.034 / 2 = 0.017
  */
  return 0.017 * pulseIn(pinEcho, HIGH);
}

/********************************/
/*********** LEDS ***************/
/********************************/

void sayHello() {
  for (byte r = 0; r < 4; r++) {
    digitalWrite(pinTest, HIGH);
    delay(500);
    digitalWrite(pinTest, LOW);
    delay(500);
  }
}

//Turn on red Led
void turnOnStopLed() {
  digitalWrite(pinGB, LOW);
  for (byte t = 0; t < 3; t++) {
    digitalWrite(pinRed, HIGH);
    delay(150);
    digitalWrite(pinRed, LOW);
    delay(150);
  }
}

//Turn on white Led
void turnOnReverseLed() {
  digitalWrite(pinRed, HIGH);
  digitalWrite(pinGB, HIGH);
}

void shutDownLed() {
  digitalWrite(pinRed, LOW);
  digitalWrite(pinGB, LOW);
}

void turnOnFrontLights() {
  setIntensityFrontLigth(250);
}

void turnOffFrontLights() {
  setIntensityFrontLigth(0);
}

void setIntensityFrontLigth(byte intensity) {
  analogWrite(pinWhite, intensity);
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
