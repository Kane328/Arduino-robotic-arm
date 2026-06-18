## PCA9685 Power Rail Issue - May 31, 2026
During initial wiring and testing, all connections appeared correct but the servo remained completely unresponsive despite the power supply being active.

### Debugging Process
Servo wired directly to the Arduino — GND to GND, power to Arduino 5V, signal to PCA9685. Servo responds correctly, ruling out the servo and signal wiring as the issue.
Power then routed through the PCA9685 board instead of directly from the Arduino. Servo becomes unresponsive again, confirming the issue lies within the board's power delivery.
A jumper wire bridged directly from the V+ screw terminal to the servo power rail on the board. Servo responds correctly.

### Final Judgment
The V+ screw terminal is not internally connected to the servo power rail by default. 
A permanent solder bridge between the two is required for reliable power delivery to all channels.

---

## Shoulder Joint Instability - June 16, 26.
During initial testing of the shoulder joint rotation, two distinct issues were observed — an audible squeak during movement and noticeable shaking while holding a position.

### Suspected Causes
- Friction between the printed rotation rail and guide is causing the squeak
- Applied load from the arm segments and payload exceeding the motor's comfortable torque range, contributing to instability

### Final Judgement 
Squeak was resolved by applying grease to the rail contact surface, eliminating friction at that interface. This is noted and applied to other similar places.

Shaking remains unresolved.

### Theories for Shaking
1. Reducing wrist and hand segment weight through design modification
2. Replacing the current motor with a higher torque alternative


