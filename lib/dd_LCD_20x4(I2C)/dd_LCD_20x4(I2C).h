#ifndef LCD_MANAGER_H
#define LCD_MANAGER_H

#include <Wire.h>               // Подключаем библиотеку для I2C
#include <LiquidCrystal_I2C.h>  // Библиотека для работы с LCD 20x4 по I2C

void dd_LCD_setup(uint8_t lcd_addr, uint8_t cols, uint8_t rows);  // Инициализация дисплея
void dd_LCD_loop();  // Обновление дисплея

void dd_LCD_setCursor(uint8_t col, uint8_t row);  // Установить курсор
void dd_LCD_clear();  // Очистить экран
void dd_LCD_print(const char* message);  // Печать строки
void dd_LCD_print(int value);  // Печать числа
void dd_LCD_print(const String &message);  // Печать строки объекта String
void dd_LCD_displayMessage(const char* message, uint8_t col, uint8_t row);  // Вывести сообщение
void dd_LCD_clearRow(int row);  // Очистить строку

#endif