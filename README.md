# Arduino-robotic-arm

<div align="center">

A 5-DOF desktop robotic arm with potentiometer-based manual control, built with 3D printed components and Arduino.

<img width="626" height="724" alt="Screenshot 2026-07-02 104837" src="https://github.com/user-attachments/assets/196ca896-08b9-46f6-851d-6be5358c5c60" />

</div>
### Components
- Arduino Uno
- 4x Positional Servo Motors (MG996R)
- 1x Continuous Servo Motor
- 1x Force sensitive resistor (FSR)
- 1x Servo Motor Driver (PCA9685)
- 4x Potentiometers (10K)
- 4V - 12V adjustable 10A DC power supply
- 22 AWG wires
- 1x Button

Main body components are 3D printed.

### How it Works
The arm has 5 degrees of freedom, with each joint independently controlled by a dedicated MG996R positional servo motor. Each servo is mapped to a potentiometer, so rotating the potentiometer causes the corresponding servo to move proportionally, allowing intuitive manual control of the arm.

All servos are driven through a PCA9685 16-channel PWM servo driver, which communicates with the Arduino via I2C using only two pins (SDA and SCL). This allows all motors to be controlled simultaneously without consuming the Arduino's limited PWM pins.
The gripper is powered by a continuous rotation servo, activated by a push button. A force-sensitive resistor (FSR) at the end of the gripper detects contact with objects and automatically stops the motor to prevent damage to the servo.

Power is supplied through an external adjustable DC power supply connected directly to the PCA9685's power rail, keeping servo current draw off the Arduino entirely.

## Wiring Diagram
<img width="1198" height="738" alt="Screenshot 2026-07-01 215328" src="https://github.com/user-attachments/assets/497bc561-188b-4f62-9e2d-d5f547a961ac" />

## Known Issues
- **Controller** — The controller is slightly out of sync with the arm.

## Future Improvements/Additions
- Apply Inverse Kinematics for independent movement
- Visual detection to pick up objects on its own
- Modular end effector system for swappable gripper types

