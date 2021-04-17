//Variables
byte shoot = 2;
byte echo = 4; 
byte ledTest = 13;

long pulseTime;
float measureDistance;

void setup() {
  // Initialize
  // Activate sensor
  Serial.begin(9600);
  
  //leds
  pinMode(ledTest, OUTPUT);
  pinMode(shoot, OUTPUT);
  pinMode(echo, INPUT);

  digitalWrite(shoot, LOW);
  digitalWrite(ledTest, LOW);
}

void loop() {
  // Shoot a signal for 10 Microseconds
  digitalWrite(shoot, HIGH);
  delayMicroseconds(10);
  digitalWrite(shoot, LOW);

  // Get the information of receipt by pin echo
  pulseTime = pulseIn(echo, HIGH);

  // Calculate the distance 340 m/s = 0.034 cm/us; 340 m/s speed of sound.
  measureDistance = 0.0340 / 2 * pulseTime;

  // Print information
  Serial.println("time/distance");
  Serial.print(pulseTime);
  Serial.print("/");
  Serial.println(measureDistance);

  // Wait to start again
  delay(500);
  
}
