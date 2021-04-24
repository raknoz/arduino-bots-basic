/*
  Formula of voltage divider
  Vout = 5V * Rldr / (Rldr + 10K); 
  without light Vout = 5V; (1024)
  with light LDR Vout = 0 ; (0)
*/

const int ledTest = 13;
const int ldrLeft = 0;
const int ldrRight = 1;

int ldrValEast = 0;
int ldrValWest = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledTest, OUTPUT);
  digitalWrite(ledTest, LOW);

  sayHello();
}

void loop() {
  //Read information of left photo-resistence 
  ldrValWest = analogRead(ldrLeft);
  delay(100);
  
  //Read information of right photo-resistence 
  ldrValEast = analogRead(ldrRight);
  delay(100);
  
  //Print information
  Serial.print(ldrValEast);
  Serial.print(" | ");
  Serial.println(ldrValWest);
  
  if (ldrValEast > ldrValWest + 150) {
    Serial.print(" Morning ");
  } if(ldrValEast < 500 && ldrValWest < 500) {
    Serial.print(" Med day ");
  } if (ldrValWest > ldrValEast + 150) {
    Serial.print(" Afternoon ");
  } else {
    Serial.print(" Night ");
  }

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