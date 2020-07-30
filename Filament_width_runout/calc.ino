void calc_width() {
  read_hall();
  int cal_value = (hall_value - (int) v_min);
  float diff_cal_rod = (float) (h_val - l_val) / 100; // Calibration Rod differenz (f.e. 2mm - 1.5mm)
  float zaehler =  cal_value * diff_cal_rod;
  int diff_call_hall = v_max - v_min; // Maximum Calibration Value - Minimum Calibration Value of the Hall Sensor
  final_width = (zaehler / diff_call_hall) + ((float) l_val / 100);
}
