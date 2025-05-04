#include <Wire.h>
#include <math.h>
#define SDA_PIN             17  //Used for bit-banging
#define SCL_PIN             16  //"
#define NUM_INIT_COMMANDS   18  
#define X_UPPERBOUND        128 //Column-resolution
#define X_LOWERBOUND        0
#define Y_UPPERBOUND        64  //Row resolution
#define Y_LOWERBOUND        0
#define NUM_PAGES           8   //pages used in addressing mode
#define SLAVE_ADDRESS       (0x78 >> 1) //shifted for Wire library
#define COMMAND_CTRL_BYTE   0x00
#define DATA_CTRL_BYTE      0x40

uint8_t display_buffer[NUM_PAGES][X_UPPERBOUND] = {0};

void setup() {
  Wire.setSDA(0);
  Wire.setSCL(1);
  Wire.begin();
  Serial.begin(9600);           //For debug
  while (!Serial);              //" 
  initDisplay();
  clearDisplay();
  delay(1000);
}
//draws pixels with a gap, then fills them
void loop() {         

    // for(int i = 0; i < 64; i++){
    //   drawPixel(64, i);
    //   display();
    //   delay(1);
    // }
    // for(int i = 0; i < 64; i++){
    //   erasePixel(64, i);
    //   display();
    //   delay(1);
    // }
    for(int i = 0; i < 1024; i++){
      uint8_t col = i % 128;
      uint8_t page = i / 128;
      sendCommand((uint8_t[]){ 0x21, col, col }, 3);
      sendCommand((uint8_t[]){ 0x22, page, page }, 3);
      Wire.beginTransmission(SLAVE_ADDRESS);
      Wire.write(DATA_CTRL_BYTE);
      Wire.write(0xFF);
      Wire.endTransmission();
      delay(5);
    }
    for(int i = 0; i < 1024; i++){
      uint8_t col = i % 128;
      uint8_t page = i / 128;
      sendCommand((uint8_t[]){ 0x21, col, col }, 3);
      sendCommand((uint8_t[]){ 0x22, page, page }, 3);
      Wire.beginTransmission(SLAVE_ADDRESS);
      Wire.write(DATA_CTRL_BYTE);
      Wire.write(0x00);
      Wire.endTransmission();
      delay(5);
    }
    clearDisplay();
}

void drawPixel(int x, int y){
  if (x >= X_UPPERBOUND || x < X_LOWERBOUND || y >= Y_UPPERBOUND || y < Y_LOWERBOUND){   
    return;
  }
  uint8_t bit_num = y % 8;
  y = y/8;
  uint8_t mask = 1 << bit_num;
  display_buffer[y][x] |= mask;
}

void erasePixel(int x, int y){
  if (x >= X_UPPERBOUND || x < X_LOWERBOUND || y >= Y_UPPERBOUND || y < Y_LOWERBOUND){   
    return;
  }
  uint8_t bit_num = y % 8;
  y = y/8;
  uint8_t mask = ~(1 << bit_num);
  display_buffer[y][x] &= mask;
}

void drawSquare(int x, int y, uint8_t w, uint8_t h){
  for(uint8_t LR = y; LR < y+h; LR++){
    drawPixel(x,LR);
    drawPixel(x + w - 1,LR);
  }
  for(uint8_t TB = x; TB < x + w; TB++){
    drawPixel(TB,y);
    drawPixel(TB,y + h - 1);
  }
}

void eraseSquare(int x, int y, uint8_t w, uint8_t h){
  for(uint8_t i = y; i < y+h; i++){
    erasePixel(x,i);
    erasePixel(x + w - 1,i);
  }
  for(uint8_t i = x; i < x + w; i++){
    erasePixel(i,y);
    erasePixel(i,y + h - 1);
  }
}

void circleUtil(int xc, int yc, int x, int y, uint8_t erase){
    if(erase == 0){
      drawPixel(xc+x, yc+y);
      drawPixel(xc-x, yc+y);
      drawPixel(xc+x, yc-y);
      drawPixel(xc-x, yc-y);
      drawPixel(xc+y, yc+x);
      drawPixel(xc-y, yc+x);
      drawPixel(xc+y, yc-x);
      drawPixel(xc-y, yc-x);
    }
    else{
      erasePixel(xc+x, yc+y);
      erasePixel(xc-x, yc+y);
      erasePixel(xc+x, yc-y);
      erasePixel(xc-x, yc-y);
      erasePixel(xc+y, yc+x);
      erasePixel(xc-y, yc+x);
      erasePixel(xc+y, yc-x);
      erasePixel(xc-y, yc-x);
    }
    
}

// Algorithm source:   https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
void drawCircle(int xc, int yc, int r){
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;
    circleUtil(xc, yc, x, y, 0);
    while (y >= x){
        if (d > 0) {
            y--; 
            d = d + 4 * (x - y) + 10;
        }
        else{
          d = d + 4 * x + 6;
        }
        x++;  
        circleUtil(xc, yc, x, y, 0);
    }
}

// Algorithm source:   https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
void eraseCircle(int xc, int yc, int r){
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;
    circleUtil(xc, yc, x, y, 1);
    while (y >= x){
        if (d > 0) {
            y--; 
            d = d + 4 * (x - y) + 10;
        }
        else{
          d = d + 4 * x + 6;
        }
        x++;  
        circleUtil(xc, yc, x, y, 1);
    }
}


void drawLine(int x0, int y0, int x1, int y1){

}

void eraseLine(int x0, int y0, int x1, int y1){
  
}

void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2){

}

void eraseTriangle(int x0, int y0, int x1, int y1, int x2, int y2){
  
}

void display(){
  setHorizontalAddressingMode();
  resumeDisplay();
  setColumnAddressingRange();
  setRowAddressingRange();
  for(int i = 0; i < NUM_PAGES; i++){
    sendData(display_buffer[i], X_UPPERBOUND);
  }
}

void clearDisplay(){      //does NOT clear RAM, only buffer. Ram updates on display()
  for(int i = 0; i < NUM_PAGES; i++){
    for(int j = 0; j < X_UPPERBOUND; j++){
      display_buffer[i][j] = 0;
    }
  }
}

void initDisplay(){
  displayOFF();
  sendCommand((uint8_t[]){0xA8, 0x3F}, 2);      //Set mux ratio
  sendCommand((uint8_t[]){0xD3, 0x00}, 2);      //set display offset
  sendCommand((uint8_t[]){0x40}, 1);            //Set Display start line
  sendCommand((uint8_t[]){0xA0}, 1);            //Set Segment Re-map, A1 <-> A0 to change HOR reflection
  sendCommand((uint8_t[]){0xC0}, 1);            //Set COM output scan direction, C0 <-> C8 to change VERT reflection
  sendCommand((uint8_t[]){0xDA, 0x02}, 2);      //Set COM pin HW config
  setContrast(0x7F);
  resumeDisplay();                              //Disable allPixelsOn()
  normalDisplay();                              //non-inverted
  sendCommand((uint8_t[]){0xD5, 0x80}, 2);      //Set Osc Freq
  sendCommand((uint8_t[]){0x8D, 0x14}, 2);      //Enable Charge Pump regulator
  setHorizontalAddressingMode();
  displayON();
}

void setRowAddressingRange(){  
  uint8_t command[] = {0x22, 0x00, (NUM_PAGES-1)};
  sendCommand(command, 3);
}

void setColumnAddressingRange(){    
  uint8_t command[] = {0x21, 0x00, (X_UPPERBOUND-1)};
  sendCommand(command, 3);
}

void resumeDisplay(){       //Display from GDDRAM
  uint8_t command[] = {0xA4};
  sendCommand(command, 1);
}

void displayON(){         //Wake display from sleep mode
  uint8_t command[] = {0xAF};
  sendCommand(command, 1);
}

void displayOFF(){        //sleep mode
  uint8_t command[] = {0xAE};
  sendCommand(command, 1);
}

void allPixelsOn(){
  uint8_t command[] = {0xA5};
  sendCommand(command, 1);
}

void normalDisplay(){     //un-invert display
  uint8_t command[] = {0xA6};
  sendCommand(command, 1);
}

void inverseDisplay(){     //invert display
  uint8_t command[] = {0xA7};
  sendCommand(command, 1);
}

void setContrast(uint8_t contrast){
  uint8_t command[] = {0x81, contrast};
  sendCommand(command, 2);
}

uint8_t sendCommand(const uint8_t * dataStream, uint8_t size){
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(COMMAND_CTRL_BYTE);
  Wire.write(dataStream, size);
  uint8_t err = Wire.endTransmission();
  if(err) {
    Serial.printf("CMD err %u\n", err);
  }else{
    Serial.print("CMD good");
  }
  return err;
}

uint8_t sendData(const uint8_t* dataStream, uint8_t size){
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(DATA_CTRL_BYTE);
  Wire.write(dataStream, size);
  uint8_t err = Wire.endTransmission();
  if(err) {
    Serial.printf("DATA err %u\n", err);
  }else{
    Serial.print("DATA good\n");
  }
  return err;
}

void setVerticalAddressingMode(){
  sendCommand((uint8_t[]){ 0x20, 0x01 }, 2);
}

void setHorizontalAddressingMode(){
  sendCommand((uint8_t[]){ 0x20, 0x00 }, 2);    //set horizontal addressing mode
}
