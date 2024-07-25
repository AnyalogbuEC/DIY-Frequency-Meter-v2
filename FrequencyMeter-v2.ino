/*
   Arduino Macro Frequency Counter

   AnyalogbuEC Designs
   Thu 11 July, 2024.

   NOTES: Signal must be logic level
          Input pin is D5
          No analogWrite() on 3, 9, 10, 11
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//FreqCount library for you know...counting frequencies
#include <FreqCount.h>
// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Function to display frequency with unit conversion
void displayFrequency(float frequency) {
  if (frequency > 1000000) { // Display in MHz
    lcd.print(frequency / 1000000, 3); // Display with 2 decimal places
    lcd.print("MHz");
  } else if (frequency > 1000) { // Display in kHz
    lcd.print(frequency / 1000, 3); // Display with 1 decimal place
    lcd.print("kHz");
  } else {
    lcd.print(frequency, 3); // Display in Hz with 1 decimal place
    lcd.print("Hz");
  }
}

void setup() {
  lcd.init(); // Initialize the LCD display
  lcd.backlight(); // Turn on LCD backlight (optional)
  lcd.clear(); // Clear the LCD display
  FreqCount.begin(1000); //start counting 1,2,3,4...
}
void loop() {
  if (FreqCount.available()) {
    // if the code if working
    float frequency = FreqCount.read();
    float period = (1 / frequency);
    // Display information on LCD
    lcd.clear();
    lcd.print("Freq:");
    displayFrequency(frequency);
    lcd.setCursor(0, 1);
    lcd.print("Period:");
    lcd.print(period * 1000);
    lcd.print(" ms");
  }
}
//That is all, carry on.
