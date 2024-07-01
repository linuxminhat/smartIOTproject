#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C LCD(0x27, 16, 2);

#include <HX711_ADC.h>
#define LOADCELL_1
//#define LOADCELL_2

#ifdef LOADCELL_1
#define HX711_DOUT 3
#define HX711_SCK 2
#define CALIBRATION_FACTOR 429.25
#elif defined(LOADCELL_2)
#define HX711_DOUT 2
#define HX711_SCK 3
#define CALIBRATION_FACTOR 425.77
#endif
HX711_ADC LoadCell(HX711_DOUT, HX711_SCK);

float new_weight = 0;
float old_weight = 0;

void setup() {
  Serial.begin(115200);
  LCD.begin();
  LCD.backlight();
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Smart scale");
  //
  LoadCell.begin();
  LoadCell.start(3000);
  LoadCell.setCalFactor(CALIBRATION_FACTOR);
  //
  LCD.clear();
}

void loop() {
  if (Serial.available()) {
    LCD.setCursor(0, 0);
    LCD.print(Serial.readStringUntil(';'));
  }
  LoadCell.update();
  old_weight = new_weight;
  new_weight = fabs(LoadCell.getData());
  if (fabs(old_weight - new_weight) >= 5) {
    LCD.clear();
  }
  // Send weight to ESP8266 NodeMCU
  Serial.println(new_weight);
  // Print to LCD
  LCD.setCursor(9, 1);
  LCD.print(String(new_weight / 1000, 3));
  LCD.print("kg");
  delay(500);
}
