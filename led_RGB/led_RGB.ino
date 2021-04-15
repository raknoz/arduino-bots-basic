byte redLed = 9;
byte greenLed = 10;
byte blueLed = 11;
byte ledTest = 13;

byte redColor = 0;
byte greenColor = 0;
byte blueColor = 0;
byte allCollor = 0;

void setup() {
  // Setup pines
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(ledTest, OUTPUT);

  // set led color shut down | analogWrite for PWM led
  analogWrite(redLed, 0);
  analogWrite(greenLed, 0);
  analogWrite(blueLed, 0);

  digitalWrite(ledTest, LOW);

  sayHelloInSecuence(ledTest, 3, 500);
  
}

void loop() {
   /*
   * red + green
   * red + green + blue
   * red - green + blue
   * - red - green + blue
   * All ligths turn off
   */

   turnOnSecuenceLigthsRGB(redLed);
   turnOnSecuenceLigthsRGB(greenLed);
   turnOnSecuenceLigthsRGB(blueLed);

   turnOffSecuenceLigthsRGB(blueLed);
   turnOffSecuenceLigthsRGB(greenLed);
   turnOffSecuenceLigthsRGB(redLed);
}

void sayHelloInSecuence(byte ledId, byte times, int delayMilisec) {
  for (int i=0; i < times; i++){
    digitalWrite(ledId, HIGH);
    delay(delayMilisec);
    digitalWrite(ledId, LOW);
    delay(delayMilisec); 
   }
}

void turnOnSecuenceLigthsRGB(byte ledIndex) {
   for (int index= 0; index <= 255; index++) {
    analogWrite(ledIndex, index);
    delay(10);
   }
}

void turnOffSecuenceLigthsRGB(byte ledIndex) {   
   for (int index = 255; index >= 0; index--) {
    analogWrite(ledIndex, index);
    delay(10);
   }
}
