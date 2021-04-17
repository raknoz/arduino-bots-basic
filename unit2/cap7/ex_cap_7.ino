//Variables
byte shoot = 4;
byte echo = 2;
byte ledTest = 13;
byte redLed = 11;
byte greenLed = 10;
byte blueLed = 9;
int intensity = 0;
long pulseTime;
long tVal;

void setup() {
  // Init
  //Serial.begin(9600);
  pinMode(ledTest, OUTPUT);
  pinMode(shoot, OUTPUT);
  pinMode(echo, INPUT);
  
  digitalWrite(shoot, LOW);
  analogWrite(redLed, 0);
  analogWrite(greenLed, 0);
  analogWrite(blueLed, 0);

  sayHello();
}

void loop() {
  // calculate distance
  pulseTime = getInpulse();

  //Evaluate the measure
  // Less than 10cm
  if (pulseTime < 550) {
    turnOnRedLight();
  }
  // Between 20cm y 15cm
  else if ( pulseTime >= 550 && pulseTime < 860 ) {
    turnOnYellowLight();
  }
  // Between 15cm y 20cm (1140µs)
  else if (pulseTime >= 860 && pulseTime < 1140) {
    turnOnGreenLight();
  }
  else {
    turnOnWhiteLight();
  }
}

// **** Private methods ****

/*
  INICIO: Medimos la longitud del puslo entrante la
  utilizamos para medir el tiempo que ha transcurrido
  entre el envío del pulso ultrasónico y la recepción
  del rebote,es decir: desde que el pin "echo" empieza
  a recibir el rebote, HIGH, hasta que deja de hacerlo,
  LOW, la longitud del pulso entrante. El resultado lo
  da en microsegundos.
*/
long getInpulse() {
  digitalWrite(shoot, HIGH);
  delayMicroseconds(10);
  digitalWrite(shoot, LOW);
  return pulseIn(echo, HIGH);
}

void turnOnRedLight() {
  analogWrite(redLed, 255);
  analogWrite(greenLed, 0);
  analogWrite(blueLed, 0);
}

void turnOnYellowLight() {
  analogWrite(redLed, 255);
  analogWrite(greenLed, 255);
  analogWrite(blueLed, 0);
}

void turnOnGreenLight() {
  analogWrite(redLed, 0);
  analogWrite(greenLed, 255);
  analogWrite(blueLed, 0);
}

void turnOnWhiteLight() {
  tVal = constrain(pulseTime, 1140, 5700);
  intensity = map(tVal, 1140, 5700, 0, 255);
  analogWrite(redLed, intensity);
  analogWrite(greenLed, intensity);
  analogWrite(blueLed, intensity);
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
