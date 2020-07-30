void serial_check() {

  if (Serial.available()) {
    char inChar = (char)Serial.read();// add it to the inputString:

    if (inChar == '\n') {

      boolean  stringComplete1 = false;
      String inputString1;

      inputString.toLowerCase();

      //Calibration 2mm rod
      if (inputString.startsWith(F("cal2"))) {
        v_max = cval;
        ee_write();
        inputString = F("?");
      }

      // Calibration 1.5 mm rod
      if (inputString.startsWith(F("cal1"))) {
        v_min = cval;
        ee_write();
        inputString = F("?");
      }

      // Input measurement of calibration rod
      if (inputString.startsWith(F("a"))) {
        inputString1 = inputString.substring(1);
        l_val = inputString1.toInt();
        ee_write();
        inputString = F("?");
      }
      if (inputString.startsWith(F("b"))) {
        inputString1 = inputString.substring(1);
        h_val = inputString1.toInt();
        ee_write();
        inputString = F("?");
      }

      // Borders for Runout Sensor
      if (inputString.startsWith(F("l"))) {
        inputString1 = inputString.substring(1);
        lval = inputString1.toInt();
        ee_write();
        inputString = F("?");
      }
      if (inputString.startsWith(F("h"))) {
        inputString1 = inputString.substring(1);
        hval = inputString1.toInt();
        ee_write();
        inputString = F("?");
      }

      // Debug, show measured value
      if (inputString.startsWith(F("e"))) {
        debugMessage = true;
        stringComplete1 = true;
      }
      if (inputString.startsWith(F("d"))) {
        debugMessage = false;
        stringComplete1 = true;
      }

      if (! stringComplete1) {
        helpMessage();
      }
      inputString = "";
    } else {
      if ((inChar != '\r') && (inChar != ' ')) inputString += inChar;
    }

  }
}


void helpMessage()
{

  Serial.println();
  if (inputString != F("?")) {
    Serial.println(F("Ukrainian Hall based filament width  and runout sensor by Deniss"));
    Serial.println(F("Version : Sep 10 2018  see http://3dua.info/ for more information"));
    Serial.println(F("==============================     Commands     ================================"));

    Serial.println(F("[axxx] set low value for calibration a150 for 1.5 mm"));
    Serial.println(F("[bxxx] set high value for calibration b200 for 2.00 mm (250 max)"));

    Serial.println(F("[cal1] 1 step calibration with 1.5 mm rod (default low 1.5 mm value)"));
    Serial.println(F("[cal2] 2 step calibration with 2.0 mm rod (default high 2.0 mm value)"));

    Serial.println(F("[lxxx] set low value for runout l150 for 1.5 mm"));
    Serial.println(F("[hxxx] set high value for runout h200 for 2.00 mm h215 for 2.15mm (250 max)"));

    Serial.println(F("[e] enable debug messages / [d] disable debug messages"));
    Serial.println(F("[??] Show calibration raw values."));

    Serial.println(F("==============================  Setting Values  ================================"));
  }
  Serial.print(F("Low calibrationt value "));
  Serial.print((float)l_val / 100);
  Serial.println(" mm");

  Serial.print(F("High calibration value "));
  Serial.print((float)h_val / 100);
  Serial.println(" mm");

  Serial.print(F("Low runout value "));
  Serial.print((float)lval / 100);
  Serial.println(" mm");

  Serial.print(F("High runout value "));
  Serial.print((float)hval / 100);
  Serial.println(" mm");

  if (inputString == F("??")) {
    Serial.print(F("Low calibration point raw value "));
    Serial.print(v_min);  Serial.print(F(" High calibration point raw value "));
    Serial.println(v_max);
  }

}
void debug_Message() {
  calc_width();
  Serial.print(F("Current raw "));
  Serial.println(hall_value);
  Serial.print(F("Current width "));
  Serial.println(final_width);
  Serial.println("==============================");
}
