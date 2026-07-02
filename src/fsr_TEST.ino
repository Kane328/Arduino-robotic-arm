void setup() {
  Serial.begin(9600);
  Serial.println("FSR Calibration Test");
}

void loop() {
  int fsrRaw = analogRead(A5);  // raw 0-1023
  float voltage = fsrRaw * (5.0 / 1023.0);   // Convert to voltage
  
  // Estimate force
  float force = 0;
  if (fsrRaw > 0) {
    float fsrVoltage = voltage;
    float fsrResistance = (5.0 - fsrVoltage) / fsrVoltage * 10000.0;
    force = 1.0 / fsrResistance * 1000000.0;
  }

  Serial.print("Raw: ");
  Serial.print(fsrRaw);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 2);
  Serial.print("V | Approx Force indicator: ");
  Serial.println(force, 2);

  delay(100);
}
