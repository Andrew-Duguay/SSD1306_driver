
#ifndef SSD1306_H        // If this macro is NOT defined
#define SSD1306_H        // Then define it

#include "ssd1306_config.h"

void display();

void clearDisplay();

void OLED_display_init();

void normalDisplay();

void inverseDisplay();

void setContrast(char contrast);

void resumeDisplay();

void displayON();

void displayOFF();

void allPixelsOn();

void setVerticalAddressingMode();

void setHorizontalAddressingMode();

void setRowAddressingRange();

void setColumnAddressingRange();

void sendCommand(char * dataStream, int size);

void sendData(char* dataStream, int size);

void drawPixel(int x, int y);

void erasePixel(int x, int y);

#endif
