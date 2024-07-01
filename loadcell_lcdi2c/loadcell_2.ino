/********************************LCD********************************/
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

/*******************************HX711*******************************/
#include <HX711_ADC.h>
#define HX711_DOUT 2
#define HX711_SCK 3
#define CALIBRATION_FACTOR 425.77

HX711_ADC LoadCell(HX711_DOUT, HX711_SCK);

float weight;

void setup() {
  Serial.begin(115200);
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart scale");
  LoadCell.begin();
  LoadCell.start(3000);
  LoadCell.setCalFactor(CALIBRATION_FACTOR);
  lcd.clear();
}

void loop() {
  LoadCell.update();            // retrieves data from the load cell
  weight = fabs(LoadCell.getData());  // get weight value
  // Send weight to ESP8266 NodeMCU
  Serial.println(weight);
  // Print to LCD
  lcd.setCursor(9, 1);
  lcd.print(String(weight / 1000, 3));
  lcd.print("kg");
  delay(500);
}