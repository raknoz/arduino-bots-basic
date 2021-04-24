/*
  Formula of voltage divider
  Vout = 5V * Rldr / (Rldr + 10K); 
  without light Vout = 5V; (1024)
  with light LDR Vout = 0 ; (0)
*/

const int ledTest = 13;
const int ldrLeft = 0;
const int ldrRight = 1;

int ldrValRight = 0;
int ldrValLeft = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledTest, OUTPUT);
  digitalWrite(ledTest, LOW);

  sayHello();
}

void loop() {
  //Read information of left photo-resistence 
  ldrValLeft = analogRead(ldrLeft);
  delay(100);

  //Read information of right photo-resistence 
  ldrValRight = analogRead(ldrRight);
  delay(100);

  //Print information
  Serial.print(ldrValLeft);
  Serial.print(" | ");
  Serial.println(ldrValRight);
  
  delay(500);
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