#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MIN_PULSE_WIDTH  500          // Minimum pulse width (us) = 0 degrees
#define MAX_PULSE_WIDTH  2600         // Maximum pulse width (us) = 180 degrees
#define FREQUENCY        50           // PWM frequency (Hz) for servos
#define FSR_POWER        8            // Digital pin powers FSR, isolates from shared 5V rail

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // PCA9685 at default I2C address 0x40

// Analog pins for potentiometers
int potBase     = A0;
int potShoulder = A1;
int potElbow    = A2;
int potWrist    = A3;

// Digital pins
int butHand = 13;
int fsr     = A5;

// PCA9685 channel assignments
int motBase     = 0;
int motShoulder = 1;
int motElbow    = 2;
int motWrist    = 4;
int motHand     = 5;

// Hand motor config
#define FSR_THRESHOLD  700   // Raw FSR value that indicates grip contact
#define CLOSE_SPEED    280   // Pulse width for closing direction
#define OPEN_SPEED     380   // Pulse width for opening direction (opposite of close)
#define STOP           330   // Neutral pulse, no movement
#define MAX_CLOSE_TIME 490   // Maximum closing time (ms) before hard stop — prevents over-rotation

// Hand motor state tracking
unsigned long closeTimer   = 0;     // Total accumulated closing time (ms)
unsigned long segmentStart = 0;     // Timestamp when current closing segment began
bool closing               = false; // True when motor is actively closing
bool opening               = false; // True when motor is actively opening
unsigned long openStart    = 0;     // Timestamp when opening began

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);        // Set PCA9685 to 50Hz
  Serial.println("Setup done");
  pinMode(butHand, INPUT_PULLUP);   // INPUT_PULLUP: unpressed = HIGH, pressed = LOW
  pinMode(FSR_POWER, OUTPUT);
  digitalWrite(FSR_POWER, HIGH);    // Power FSR from digital pin to isolate from analog rail
}

// Reads potentiometer and sends proportional signal to servo
// map(value, fromLow, fromHigh, toLow, toHigh)
void motor(int potSent, int motMove) {
  int potVal     = analogRead(potSent);                                         // Raw pot value 0-1023
  int pulse_wide = map(potVal, 0, 1023, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);      // Scale to pulse range (us)
  int pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);       // Convert us to PCA9685 12-bit count
  pwm.setPWM(motMove, 0, pulse_width);                                          // Send to channel (channel, on-tick, off-tick)
}

void loop() {
  // Drive positional servos from potentiometers
  motor(potBase,     motBase);
  motor(potShoulder, motShoulder);
  motor(potElbow,    motElbow);
  motor(potWrist,    motWrist);

  int butPress = digitalRead(butHand); // LOW = pressed, HIGH = released
  int fsrVal   = analogRead(fsr);      // Raw FSR reading 0-1023

  // ── OPENING STATE ────────────────────────────────────────────────────────
  if (opening) {
    unsigned long elapsed = millis() - openStart;

    if (elapsed >= closeTimer) {
      // Opened for same duration as it closed — stop and reset all state
      pwm.setPWM(motHand, 0, STOP);
      opening    = false;
      closeTimer = 0;
      segmentStart = 0;
      Serial.println("Fully open - reset");
    } else {
      pwm.setPWM(motHand, 0, OPEN_SPEED); // Keep opening
    }
    delay(15);
    return; // Skip rest of loop while opening
  }

  // ── BUTTON PRESSED ───────────────────────────────────────────────────────
  if (butPress == LOW) {

    // Hard cap — prevent closing beyond max safe duration
    if (closeTimer >= MAX_CLOSE_TIME) {
      if (closing) {
        closeTimer = MAX_CLOSE_TIME; // Cap timer at max
        closing = false;
      }
      pwm.setPWM(motHand, 0, STOP);
      Serial.println("Max close time reached - stopped");

    } else if (fsrVal >= FSR_THRESHOLD) {
      // FSR threshold reached — grip detected, pause timer
      if (closing) {
        closeTimer += millis() - segmentStart; // Accumulate this segment
        closeTimer = min(closeTimer, (unsigned long)MAX_CLOSE_TIME); // Cap at max
        closing = false;
        Serial.print("Grip detected - timer paused at: ");
        Serial.println(closeTimer);
      }
      pwm.setPWM(motHand, 0, STOP);

    } else {
      // FSR below threshold — close and count time
      if (!closing) {
        segmentStart = millis(); // Start new closing segment
        closing = true;
        Serial.println("Closing...");
      }
      pwm.setPWM(motHand, 0, CLOSE_SPEED);
    }

  // ── BUTTON RELEASED ──────────────────────────────────────────────────────
  } else {
    if (closing) {
      // Save the final segment duration before stopping
      closeTimer += millis() - segmentStart;
      closeTimer = min(closeTimer, (unsigned long)MAX_CLOSE_TIME); // Cap at max
      closing = false;
    }

    if (closeTimer > 0) {
      // Reverse for exactly how long it closed
      opening   = true;
      openStart = millis();
      Serial.print("Opening for: ");
      Serial.print(closeTimer);
      Serial.println("ms");
    } else {
      pwm.setPWM(motHand, 0, STOP); // Nothing to open, stay stopped
    }
  }

  delay(15);
}