const int motorPin1 = 10;  // Pin 7 of L293
const int motorPin2 = 9;   // Pin 2 of L293
const int potpin = A0;     // Potentiometer pin
const int en1_2_pin = 3;   // Enable pin for motor speed control

void setup() {
    // Set motor pins as outputs
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(en1_2_pin, OUTPUT);
    pinMode(potpin, INPUT);
}

void loop() {
    // Read the potentiometer value
    int potValue = analogRead(potpin);

    // Map the potentiometer value (0-1023) to PWM range (0-255)
    int pwmValue = map(potValue, 0, 1023, 0, 255);

    // Logic to control motor direction and speed
    if (pwmValue < 120) { // CCW
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
        analogWrite(en1_2_pin, map(pwmValue, 0, 120, 255, 0)); // Scale speed for CCW
    } 
    else if (pwmValue > 130) { // CW
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
        analogWrite(en1_2_pin, map(pwmValue, 130, 255, 0, 255)); // Scale speed for CW
    } 
    else { // Stop motor in the dead zone (120-130)
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, LOW);
        analogWrite(en1_2_pin, 0);
    }
}
