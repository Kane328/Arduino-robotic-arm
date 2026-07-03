## PCA9685 Power Rail Issue - May 31, 2026
During initial wiring and testing, all connections appeared correct, but the servo remained completely unresponsive despite the power supply being active.

### Debugging Process
Servo wired directly to the Arduino — GND to GND, power to Arduino 5V, signal to PCA9685. Servo responds correctly, ruling out the servo and signal wiring as the issue.
Power is then routed through the PCA9685 board instead of directly from the Arduino. Servo becomes unresponsive again, confirming the issue lies within the board's power delivery.
A jumper wire bridged directly from the V+ screw terminal to the servo power rail on the board. Servo responds correctly.

### Final Solution
The V+ screw terminal is not internally connected to the servo power rail by default. 
A permanent solder bridge between the two is required for reliable power delivery to all channels.

---

## Shoulder Joint Instability - June 16, 26.
During initial testing of the shoulder joint rotation, two distinct issues occurred: a  squeak during movement and noticeable shaking while holding a position.

### Suspected Causes
- Friction between the printed rotation rail and guide is causing the squeak
- Applied load from the arm segments and payload exceeding the motor's comfortable torque range, contributing to instability

### Final Solution 
Squeak was resolved by applying grease to the rail contact surface, eliminating friction at that interface. This is noted and applied to other similar places.

Shaking remains unresolved.

### Theories for Shaking
1. Reducing wrist and hand segment weight through design modification
2. Replacing the current motor with a higher torque alternative


---
## FSR Wiring Interference - July 1, 2026
During full arm testing with the FSR connected, the entire arm would freeze and become unresponsive.

### Root Cause
Two separate issues were identified:
- The FSR shares the 5V rail with the potentiometers — the FSR's resistive behavior was pulling the shared voltage down, corrupting analog readings across all potentiometer pins
- The FSR signal and power wires were making intermittent contact with each other, causing short circuits that froze the system.

### Solution
The FSR was isolated from the shared 5V rail by powering it from a dedicated digital pin set to HIGH, eliminating interference with the potentiometer readings. The wires were additionally separated and secured with electrical tape to prevent further contact.

---

## Hand Servo Over-rotation - July 1, 2026
During hand testing, the gripper motor continued rotating past the fully open position, producing a loud ticking sound as the mechanism hit its physical limit.

### Suspected Cause
The control logic tracks how long the button is held to determine how long to reverse the motor on release (to open up fully). The close time was exceeding the actual travel time of the gripper, causing the motor to run open for longer than physically possible and lock against the mechanical stop.

### Solution
A maximum open duration of 500ms was hardcoded into the control logic, capping the reverse time regardless of how long the button was held. This ensures the motor cannot run past the fully open position.
