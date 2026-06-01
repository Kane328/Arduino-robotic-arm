# Arduino-robotic-arm
This project is to create a robotic arm controlled by an Arduino with 5 degrees of freedom.

### Components
- Arduino Uno
- 4 Positional Servo Motors (MG996R)
- 1 Continuous Servo Motor
- Force sensitive resistor (FSR)
- Servo Motor Driver (PCA9685)
- 4 Potentiometers (10K)
- 4V - 12V adjustable 10A DC power supply
- 22 AWG wires
- button

Main body components are 3D printed. Files included.

### How it Works
The arm has 5 degrees of freedom, with each joint independently controlled by a dedicated MG996R positional servo motor. Each servo is mapped to a potentiometer, so rotating the potentiometer causes the corresponding servo to move proportionally, allowing intuitive manual control of the arm.

All servos are driven through a PCA9685 16-channel PWM servo driver, which communicates with the Arduino via I2C using only two pins (SDA and SCL). This allows all motors to be controlled simultaneously without consuming the Arduino's limited PWM pins.
The gripper is powered by a continuous rotation servo, activated by a push button. A force-sensitive resistor (FSR) at the end of the gripper detects contact with objects and automatically stops the motor to prevent damage to the servo.

Power is supplied through an external adjustable DC power supply connected directly to the PCA9685's power rail, keeping servo current draw off the Arduino entirely.

## Wiring Diagram
  TBA
## Known Issues
  TBA

## Future Improvements/Additions
- Apply Inverse Kinematics for independent movement
- Visual detection to pick up objects on its own
- Different kinds of arms

