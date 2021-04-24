// OUTPUT Constants 
const byte leftTransmitter = 6;
const byte rightTransmitter = 8;

const byte ledTest = 13;

//INPUT Constants
const int leftReceipt = A0;
const int rightReceipt = A1;

// "Reflactividad" data
int leftRef;
int rightRef;


void setup() {
  //Start or initialize Serial ports
  Serial.begin(9600);

  // 
  pinMode(leftTransmitter, OUTPUT);
  pinMode(rightTransmitter, OUTPUT);
  pinMode(ledTest, OUTPUT);

  // All turn OFF

  digitalWrite(leftTransmitter, LOW);
  digitalWrite(rightTransmitter, LOW);
  digitalWrite(ledTest, LOW);

  sayHello();
}

void loop() {

  leftRef = getReflectivityByTransmitter(leftTransmitter);
  rightRef = getReflectivityByTransmitter(rightTransmitter);

  Serial.println("LEFT / RIGHT");
  Serial.print(leftRef);
  Serial.print(" , ");
  Serial.println(rightRef);
  delay(500);
}


// **** private methods ****
int getReflectivityByTransmitter(byte transmitterPin) {
  digitalWrite(transmitterPin, HIGH);
  /*
    analogRead reads from specific analog's pin's value. 
    map the inpunt tensions between 0 and 5 V in INTEGER values between 0 and 1023
  */
  int data = analogRead(transmitterPin);
  delay(100);
  digitalWrite(transmitterPin, LOW);
  return data;
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
