## PCA9685 Power Rail Issue - May 31, 2026
During initial wiring and testing, all connections appeared correct but the servo remained completely unresponsive despite the power supply being active.

### Debugging Process
Servo wired directly to the Arduino — GND to GND, power to Arduino 5V, signal to PCA9685. Servo responds correctly, ruling out the servo and signal wiring as the issue.
Power then routed through the PCA9685 board instead of directly from the Arduino. Servo becomes unresponsive again, confirming the issue lies within the board's power delivery.
A jumper wire bridged directly from the V+ screw terminal to the servo power rail on the board. Servo responds correctly.

### Final Judgment
The V+ screw terminal is not internally connected to the servo power rail by default. 
A permanent solder bridge between the two is required for reliable power delivery to all channels.

