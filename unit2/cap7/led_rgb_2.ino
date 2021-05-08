//variables
byte rightBlankLed = 2;
byte leftBlackLed = 4;
byte rightRedLed = 7;
byte leftRedLed = 8;
byte ledTest = 13; 

void setup() {
  /*
   * pinMode (range-of-pines, MODE {INPUT, OUTPUT})
   * If you put a only one pin, then only config that pin.
   */
  pinMode(rightBlankLed, OUTPUT);
  pinMode(leftBlackLed, OUTPUT);
  pinMode(rightRedLed, OUTPUT);
  pinMode(leftRedLed, OUTPUT);

  /*
   * digitalWrite(range, SIGNAL);
   * Signal LOW(off) or HIGH(on) to some specific pin.
   */
  digitalWrite(rightBlankLed, LOW);
  digitalWrite(leftBlackLed, LOW);
  digitalWrite(rightRedLed, LOW);
  digitalWrite(leftRedLed, LOW);

  pinMode(ledTest, OUTPUT);
  digitalWrite(ledTest, LOW);

  //Initial Hello 3 times
   for (int i=0; i < 3; i++){
    digitalWrite(ledTest, HIGH);
    delay(500);
    digitalWrite(ledTest, LOW);
    delay(500); 
   }
}

void loop() {
  // Turn ON all the leds
  // turnOnAllLigths(1000);

  turnOnLigthsSecuence(rightBlankLed, 5, 500);
  turnOnLigthsSecuence(leftBlackLed, 10, 250);
  turnOnLigthsSecuence(rightRedLed, 5, 750);
  turnOnLigthsSecuence(leftRedLed, 10, 1000);

  // Turn OFF all the leds
  // turnOffAllLigths(1000);
}


void turnOnAllLigths(int delayMilisec) {
  digitalWrite(rightBlankLed, HIGH);
  digitalWrite(leftBlackLed, HIGH);
  digitalWrite(rightRedLed, HIGH);
  digitalWrite(leftRedLed, HIGH);
  delay(delayMilisec);
}

void turnOffAllLigths(int delayMilisec) {
  digitalWrite(rightBlankLed, LOW);
  digitalWrite(leftBlackLed, LOW);
  digitalWrite(rightRedLed, LOW);
  digitalWrite(leftRedLed, LOW);
  delay(delayMilisec);
}

void turnOnLigthsSecuence(byte ledId, byte times, int delayMilisec) {
  for (int i=0; i < times; i++){
    digitalWrite(ledId, HIGH);
    delay(delayMilisec);
    digitalWrite(ledId, LOW);
    delay(delayMilisec); 
   }
}
