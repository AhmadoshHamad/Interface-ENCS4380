#include <LiquidCrystal.h>

// Define motor pins
const int motorPin1 = 10;  // Pin 7 of L293
const int motorPin2 = 9;   // Pin 2 of L293
const int potpin = A0;     // Potentiometer pin
const int en1_2_pin = 11;   // Enable pin for motor speed control

// Define encoder pins
const int encoderPinA = 2;  // Encoder pin A
const int encoderPinB = 12; // Encoder pin B (updated to avoid conflict)

// Initialize encoder variables
volatile int encoderValue = 0;
int lastEncoderValue = 0;

// LCD pins:     RS, E, D4,D5,D6, D7
LiquidCrystal lcd(7, 8, 6, 5, 4, 3); // LCD pin assignments remain unchanged


void setup() {
    // Set motor pins as outputs
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(en1_2_pin, OUTPUT);
    pinMode(potpin, INPUT);

    // Set encoder pins as inputs
    pinMode(encoderPinA, INPUT_PULLUP);
    pinMode(encoderPinB, INPUT_PULLUP);

    // Attach interrupt to encoder pins
    attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderPinB), updateEncoder, CHANGE);

    // Initialize Serial and LCD
    Serial.begin(9600);
    lcd.begin(16, 2); // Set LCD to 16x2 characters
    // lcd.print("Encoder Value:");
}

void loop() {
    // Read the potentiometer value
    int potValue = analogRead(potpin);

    // Map the potentiometer value (0-1023) to PWM range (0-255)
    int pwmValue = map(potValue, 0, 1023, 0, 255);

    // Logic to control motor direction and speed
    if (pwmValue < 110) { // CCW
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
        analogWrite(en1_2_pin, map(pwmValue, 0, 109, 255, 0)); // Scale speed for CCW
    } 
    else if (pwmValue > 150) { // CW
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
        analogWrite(en1_2_pin, map(pwmValue, 151, 255, 0, 255)); // Scale speed for CW
    } 
    else { // Stop motor in the dead zone (110-150)
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, LOW);
        analogWrite(en1_2_pin, 0);
    }

    // Display the encoder value on the LCD
    if (encoderValue != lastEncoderValue) {
        lcd.setCursor(0, 1); // Move to the second line
        lcd.print("Speed: ");
        lcd.print(pwmValue);

        lcd.setCursor(0, 0); // Move to the second line
        lcd.print("pos: ");
        lcd.print(encoderValue);
        
        lastEncoderValue = encoderValue;
    }
}

// Interrupt service routine to update encoder value
void updateEncoder() {
    int stateA = digitalRead(encoderPinA);
    int stateB = digitalRead(encoderPinB);

    if (stateA == HIGH) {
        if (stateB == LOW) {
            encoderValue++; // CW rotation
        } else {
            encoderValue--; // CCW rotation
        }
    } else {
        if (stateB == HIGH) {
            encoderValue++; // CW rotation
        } else {
            encoderValue--; // CCW rotation
        }
    }
}
