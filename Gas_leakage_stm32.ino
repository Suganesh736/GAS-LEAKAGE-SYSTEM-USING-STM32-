#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define MQ2_PIN PA0
#define BUZZER_PIN PA1

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

#define GAS_THRESHOLD 100

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

int gasValue = 0;

void setup()
{
  pinMode(MQ2_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);

  // STM32 I2C pins
  Wire.setSDA(PB7);
  Wire.setSCL(PB6);
  Wire.begin();

  // Set ADC resolution to 12 bits
  analogReadResolution(12);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(15, 20);
  display.println("GAS DETECTION");
  display.display();

  delay(2000);
}

void loop()
{
  // Read exact ADC value from MQ2 sensor
  gasValue = analogRead(MQ2_PIN);

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(15, 5);
  display.println("GAS MONITORING");

  display.setCursor(5, 25);
  display.print("Sensor Value: ");
  display.println(gasValue);

  display.setCursor(5, 40);
  display.print("Threshold: ");
  display.println(GAS_THRESHOLD);

  // Gas threshold condition
  if (gasValue >= GAS_THRESHOLD)
  {
    digitalWrite(BUZZER_PIN, HIGH);

    display.setCursor(5, 55);
    display.println("GAS ALERT! BUZZER ON");
  }
  else
  {
    digitalWrite(BUZZER_PIN, LOW);

    display.setCursor(5, 55);
    display.println("SAFE - BUZZER OFF");
  }

  display.display();

  delay(500);
}