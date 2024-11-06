#define TRIG_PIN 9   
#define ECHO_PIN 10  
#define red 5
#define yellow 6
#define green 7 


#define lowerBound 10
#define upperBound 20



void setup() {
  Serial.begin(9600); // Start serial communication for output
  pinMode(TRIG_PIN, OUTPUT); // Set TRIG as output
  pinMode(ECHO_PIN, INPUT);  // Set ECHO as input
  pinMode(A0,INPUT);
  // setup leds
  pinMode(red,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
}

void loop() {
  // Send a pulse on the TRIG pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);   // Send a 10-microsecond pulse
  digitalWrite(TRIG_PIN, LOW);
  int pot = analogRead(A0);
  // Measure the time taken by the pulse to return to the ECHO pin
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance in cm (speed of sound is ~343 m/s or ~0.0343 cm/μs)
  float distanceCm = (duration * 0.0343) / 2;

  int factor = pot/333 + 1;



  if(distanceCm < (lowerBound * factor) ){
    digitalWrite(red, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
  }

  else if(distanceCm > (upperBound * factor)){
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, HIGH);
  }
  else {
     
    digitalWrite(red, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(green, LOW);
  
  }



  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");
  Serial.print("pot : ");
  Serial.println(pot);
  Serial.print("factor : ");
  Serial.println(factor);
  

  delay(750); // Delay before next measurement
}
