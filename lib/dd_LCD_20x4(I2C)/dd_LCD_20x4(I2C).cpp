#include "dd_LCD_20x4(I2C).h"

LiquidCrystal_I2C lcd(0x27, 20, 4);  // Create an LCD object

void dd_LCD_setup(uint8_t lcd_addr, uint8_t cols, uint8_t rows) {
    lcd = LiquidCrystal_I2C(lcd_addr, cols, rows);  // Initialize the LCD object
    lcd.init();  // Initialize the display
    lcd.backlight();  // Turn on the backlight
    lcd.clear();  // Clear the display
    lcd.setCursor(0, 0);  // Set the cursor to the top-left corner
}

void dd_LCD_loop() {
    // Add your display update logic here
    lcd.setCursor(0, 0);
    lcd.print("Updated Display");
}

void dd_LCD_setCursor(uint8_t col, uint8_t row) {
    lcd.setCursor(col, row);
}

void dd_LCD_clear() {
    lcd.clear();
}

void dd_LCD_print(const char* message) {
    lcd.print(message);
}

void dd_LCD_print(int value) {
    lcd.print(value);
}

void dd_LCD_print(const String &message) {
    lcd.print(message);
}

void dd_LCD_displayMessage(const char* message, uint8_t col, uint8_t row) {
    lcd.setCursor(col, row);
    lcd.print(message);
}

void dd_LCD_clearRow(int row) {
    lcd.setCursor(0, row);  // Move cursor to the start of the specified row
    for (int i = 0; i < 20; i++) {  // Assuming a 20-character wide LCD
        lcd.print(" ");  // Print a space to clear each character
    }
    lcd.setCursor(0, row);  // Return the cursor to the start of the row
}