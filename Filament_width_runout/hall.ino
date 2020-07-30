void read_hall() { // Read Hall Sensors and produce an avereage value
  unsigned int a = 0; //If no filament is inserted, the measured values do not fit into an INT
  for (byte t = 0; t < 30; t++) { // ~1s cycle //Average
    a += analogRead(hall1_pin) + analogRead(hall2_pin); //Read Hall Sensors; Value of Sensor 1 + Value of Sensor 2; accumulated 30 times (loop)
    delay(1);
  }
  a = a / 6;
  hall_value = a;
}

void write_ext() {
  int width = final_width * 100;
  pw = (float) 1024 / 450 * width; // Resolution (10Bit) / 4.5V Volts * Measured value
  //Maximum 4.5V, prevent 255 as Value; 255 is the same as 1023 = 4.5V
  //ADC on BTT is maximum 3.3V  -> limit the Voltage
  //Range from 0-4.5 V with a 1024 steps = 0,0044V per step
  if (pw > 568) {
    pw = 568;
  }

  if (pw == 255) {
    pw = 256;
  }

  analogWrite(10, pw);
}
