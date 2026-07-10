Design of the wiring diagram is all done using the site, app.cirkitdesigner.com

## Wiring Notes ##
- The PCA9685 board received had a manufacturing defect where the V+ screw terminal was not internally connected to the servo power rail. A soldered wire bridge from V+ to V+ and GND to GND was required to resolve this; this is not standard and may not apply to all boards.
- Channel 3 on the PCA9685 is left empty due to the defect on this specific board. Servo channels can be reassigned as needed; just update the corresponding channel number in the Arduino code.
- The FSR is powered from digital pin 8 on the Arduino rather than the shared 5V rail. This is to isolate the FSR from the potentiometer analog circuit, preventing voltage interference that was found to freeze the arm during testing. Pin 8 can be consolidated with the shared 5V rail if interference is not an issue on your setup.
- The OE (Output Enable) pin on the PCA9685 is connected to GND to permanently enable output. If left floating, outputs may randomly disable.
  
- Power is supplied externally at 5-6V directly to the PCA9685 power rail; do not exceed 7.2V as this is the maximum operating voltage of the MG996R servos.
- The Arduino is powered separately via USB. Do not route servo power through the Arduino as it cannot supply sufficient current for multiple servos simultaneously.
