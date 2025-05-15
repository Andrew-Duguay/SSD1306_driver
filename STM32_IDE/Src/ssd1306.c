#include "ssd1306.h"
#include "ssd1306_config.h"
#include "i2c.h"

char display_buffer[NUM_PAGES * SCREEN_WIDTH] = {0};

void display(){
  setHorizontalAddressingMode();
  resumeDisplay();
  setColumnAddressingRange();
  setRowAddressingRange();
  sendData(display_buffer, NUMBER_OF_BYTES);
}

void clearDisplay(){      //does NOT clear RAM, only buffer. Ram updates on display()
  for(int i = 0; i < NUMBER_OF_BYTES; i++){
      display_buffer[i] = 0;
  }
}

void OLED_display_init(){
	displayOFF();
	sendCommand((char[]){0xA8, 0x3F}, 2);      //Set mux ratio
	sendCommand((char[]){0xD3, 0x00}, 2);      //set display offset
	sendCommand((char[]){0x40}, 1);            //Set Display start line
	sendCommand((char[]){0xA0}, 1);            //Set Segment Re-map, A1 <-> A0 to change HOR reflection
	sendCommand((char[]){0xC0}, 1);            //Set COM output scan direction, C0 <-> C8 to change VERT reflection
	sendCommand((char[]){0xDA, 0x12 /*0x02*/}, 2);      //Set COM pin HW config
	setContrast(0x7F);
	resumeDisplay();                              //Disable allPixelsOn()
	normalDisplay();                              //non-inverted
	sendCommand((char[]){0xD5, 0x80}, 2);      //Set Osc Freq
	sendCommand((char[]){0x8D, 0x14}, 2);      //Enable Charge Pump regulator
	setHorizontalAddressingMode();
	displayON();
}

void normalDisplay(){     //un-invert display
	char command[] = {0xA6};
	sendCommand(command, 1);
}

void inverseDisplay(){     //invert display
	char command[] = {0xA7};
	sendCommand(command, 1);
}

void setContrast(char contrast){
	char command[] = {0x81, contrast};
	sendCommand(command, 2);
}

void resumeDisplay(){       //Display from GDDRAM
	char command[] = {0xA4};
	sendCommand(command, 1);
}

void displayON(){         //Wake display from sleep mode
	char command[] = {0xAF};
	sendCommand(command, 1);
}

void displayOFF(){        //sleep mode
	char command[] = {0xAE};
	sendCommand(command, 1);
}

void allPixelsOn(){
	char command[] = {0xA5};
    sendCommand(command, 1);
}

void setVerticalAddressingMode(){
	sendCommand((char[]){ 0x20, 0x01 }, 2);
}

void setHorizontalAddressingMode(){
	sendCommand((char[]){ 0x20, 0x00 }, 2);    //set horizontal addressing mode
}

void setRowAddressingRange(){
	char command[] = {0x22, 0x00, (NUM_PAGES-1)};
	sendCommand(command, 3);
}

void setColumnAddressingRange(){
	char command[] = {0x21, 0x00, (SCREEN_WIDTH-1)};
	sendCommand(command, 3);
}

void sendCommand(char * dataStream, int size){
	I2C1_burstWrite((char)SLAVE_ADDRESS, (char)COMMAND_CTRL_BYTE, size, dataStream);
}

void sendData(char* dataStream, int size){
	I2C1_burstWrite((char)SLAVE_ADDRESS, (char)DATA_CTRL_BYTE, size, dataStream);
}

void drawPixel(int x, int y){
  if (x >= SCREEN_WIDTH || x < 0 || y >= SCREEN_HEIGHT || y < 0){
    return;
  }
  char bit_num = y % BITS_PER_PAGE;
  int page = y/NUM_PAGES;
  char mask = 1 << (bit_num);
  int byte_index = page * SCREEN_WIDTH + x;
  display_buffer[byte_index] |= mask;
}

void erasePixel(int x, int y){
  if (x >= SCREEN_WIDTH || x < 0 || y >= SCREEN_HEIGHT || y < 0){
    return;
  }
  char bit_num = y % BITS_PER_PAGE;
  int page = y/NUM_PAGES;
  char mask = ~(1 << (bit_num));
  int byte_index = page * SCREEN_WIDTH + x;
  display_buffer[byte_index] &= mask;
}
