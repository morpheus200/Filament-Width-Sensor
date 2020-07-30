#include <EEPROM.h>

byte lval, hval, l_val, h_val;
unsigned int v_min, v_max, cval;
int hall_value, pw;
boolean debugMessage;
String inputString;
float final_width;
#define hall1_pin 2
#define hall2_pin 3
#define runout_pin 7
#define runout_buzzer_pin 6

void setup() {
  // TCCR1A TCCR1B Timer Controll Register   pins 9 and 10 are controlled by TCCR1B
  TCCR1A = TCCR1A & 0xe0 | 3;     // set for pin 10   // | 3 = PWM, Phase Correct, 10-bit 0x03FF TOP BOTTOM
  TCCR1B = TCCR1B & 0xe0 | 0x09;  // 10 bit PWM 15625 Hz 0.005 V resolution

  Serial.begin(115200);
  ee_read();
  helpMessage();
  inputString = "";
  pinMode(12, OUTPUT); // For ground capacitor
  pinMode(10, OUTPUT);
  pinMode(11, INPUT); // using for DAC output. Software disconected from atmega
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(runout_pin, OUTPUT);
  digitalWrite(runout_pin, HIGH);
  pinMode(runout_buzzer_pin, OUTPUT);
  digitalWrite(runout_buzzer_pin, HIGH);

  digitalWrite(12, LOW); // For ground capacitor
}

void loop() {

  for (byte t = 0; t < 67; t++) { // ~2s cycle
    read_hall();
    calc_width();
    write_ext();
    serial_check();
    if ((final_width > hval) || (final_width < lval)) {
      pinMode(runout_pin, LOW);   digitalWrite(LED_BUILTIN, HIGH);
      if (t < 45) pinMode(runout_buzzer_pin, LOW); else pinMode(runout_buzzer_pin, HIGH);
    }
    else
    {
      pinMode(runout_buzzer_pin, HIGH);  // check limits
      pinMode(runout_pin, HIGH);
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
  if (debugMessage)  debug_Message();


}
