#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MIN_PULSE_WIDTH  500
#define MAX_PULSE_WIDTH  2600
#define FREQUENCY        50

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Set Pin Values
int potBase = A0;
int potShoulder = A1;
int potElbow = A2;
int potWrist = A3;
int butHand = 13;

int motBase = 0;
int motShoulder = 1;
int motElbow = 2;
int motWrist = 3;
int motHand = 4;

void setup() {
  // Positional Servo Setup
  Serial.begin(9600);             // Serial connection between Arduino and computer, 9600 bits/s
  pwm.begin();                    // Wakes PCA9685 board
  pwm.setPWMFreq(FREQUENCY);      // Tells PCA 9685 board to set signals at the set frequency (50 Hz)
  Serial.println("Setup done");  
   
  // Continous Servo Setup
  pinMode(butHand, INPUT_PULLUP); // Convert the button output to a LOW (pressed) and HIGH (unpressed)
  
}

// A function that takes the potentiometer value and moves motor accordingly
void motor(int potSent, int motMove) {
  int potVal = analogRead(potSent);                                                     // Reads the potentiometer at pin potSent... potBase, potShoulder, etc
  int pulse_wide = map(potVal, 0, 1023, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);              // Scales the pot value to the appropiate range
  int pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  pwm.setPWM(motMove, 0, pulse_width);                                                  // Sends signal to Servo, pwm.setPWM(channel #, when in cycle to turn on, when in cycle to turn off*reaches specific angle)

}

void loop() {
  // Controlling the Positional Servos, applying above function
  motor(potBase,motBase);     
  motor(potShoulder,motShoulder);
  motor(potElbow,motElbow);
  motor(potWrist,motWrist);

  int butPress = digitalRead(butHand);
  if (butPress == LOW) {  //LOW -> Pressed
    pwm.setPWM(motHand, 0, 400);  // (pin #,... ,pulse value corresponding to some speed)
  }
  else {  // Otherwise HIGH, unpressed
    pwm.setPWM(motHand, 0, 330);  // (pin #,... ,pulse value corresponding to no movement)
  }

  delay(15);  // Give some time for Servo to recive information and not be overloaded


  
}
