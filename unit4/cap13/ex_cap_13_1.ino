#include <IRremote.h>
#include <IRremoteInt.h>

byte ledTest = 13;
byte receptorIR = 2;

IRrecv receptorIr(receptorIR);

decode_results results;

byte redPin = 9;
byte greenPin = 10;
byte bluePin = 6;

int potenciaRed = 0;
int potenciaGreen = 0;
int potenciaBlue = 0;

void setup() {
  Serial.begin(9600);
  receptorIr.enableIRIn(); // init to start receipr signals

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);

  pinMode(ledTest, OUTPUT);
  digitalWrite(ledTest, LOW);

  sayHello();
}

void sayHello() {
  digitalWrite(ledTest, HIGH);
  delay(500);
  digitalWrite(ledTest, LOW);
  delay(500);
  digitalWrite(ledTest, HIGH);
  delay(500);
  digitalWrite(ledTest, LOW);
  delay(500);
  digitalWrite(ledTest, HIGH);
  delay(500);
  digitalWrite(ledTest, LOW);
  delay(500);
}

void loop() {

  if (receptorIr.decode(&results)) {
    Serial.println(results.value, HEX);

    switch (results.value) {
      case 0xFF30CF:
        turnOnredPin(0);
        break;
      case 0xFF18E7:
        turnOnredPin(127);
        break;
      case 0xFF7A85:
        turnOnredPin(255);
        break;
      case 0xFF10EF:
        turnOngreenPin(0);
        break;
      case 0xFF38C7:
        turnOngreenPin(127);
        break;
      case 0xFF5AA5:
        turnOngreenPin(255);
        break;
      case 0xFF42BD:
        turnOnbluePin(0);
        break;
      case 0xFF4AB5:
        turnOnbluePin(127);
        break;
      case 0xFF52AD:
        turnOnbluePin(255);
        break;
      case 0xFFA25D:
        analogWrite(redPin, 0);
        analogWrite(greenPin, 0);
        analogWrite(bluePin, 0);
        break;
      case 0xFFE21D:
        analogWrite(redPin, 255);
        analogWrite(greenPin, 255);
        analogWrite(bluePin, 255);
        break;
      default:
        digitalWrite(ledTest, HIGH);
        delay(200);
        digitalWrite(ledTest, LOW);
        delay(200);
        digitalWrite(ledTest, HIGH);
        delay(200);
        digitalWrite(ledTest, LOW);
        break;
    }
    receptorIr.resume(); // Receive the next value
    delay(100);
  }
}

void turnOngreenPin(int intensity) {
  analogWrite(redPin, 0);
  analogWrite(greenPin, intensity);
  analogWrite(bluePin, 0);
}

void turnOnredPin(int intensity) {
  analogWrite(redPin, intensity);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
}

void turnOnbluePin(int intensity) {
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, intensity);
}
