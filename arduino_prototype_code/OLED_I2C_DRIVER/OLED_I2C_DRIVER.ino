#define SDA_PIN 17
#define SCL_PIN 16

void latchBit();
void sendData(uint8_t dataStream[], uint8_t size);
void sendCommand(uint8_t dataStream[], uint8_t size);
void setContrast(uint8_t contrast);
void invertDisplay();
void normalDisplay();
void displayMode();
void allPixelsOn();
void displayOFF();
void displayON();
void resumeDisplay();
bool checkACK();
void sendByte(uint8_t byte);
void initDisplay();

uint8_t display_buffer[8][128] = {0};
uint8_t init_seq[24] = {  0xA8, 0x3F,   //Set mux ratio
                          0xD3, 0x00,   //set display offset
                          0x40,         //Set Display start line
                          0xA0,         //Set Segment Re-map, A1 <-> A0 to change HOR reflection
                          0xC0,          //Set COM output scan direction, C0 <-> C8 to change VERT reflection
                          0xDA, 0x02,   //Set COM pin HW config
                          0x81, 0x7F,   //set contrast to 0x7F/0xFF
                          0xA4,         //Disable Entire Display On
                          0xA6,         //Set Normal Display
                          0xD5, 0x80,   //Set Osc Freq
                          0x8D, 0x14,   //Enable Charge Pump regulator
                          0xAF         //Display on
                        };


void setup() {
  pinMode(SDA_PIN, OUTPUT);
  pinMode(SCL_PIN, OUTPUT);
  digitalWrite(SCL_PIN, HIGH);
  digitalWrite(SDA_PIN, HIGH);
  initDisplay();
  delay(5);
}

void loop() {
  while(1){}
}

void clearDisplay(){
  // sendCommand()
  // display_buffer = {0};
}

void initDisplay(){
  sendCommand(init_seq, 18);
  digitalWrite(SDA_PIN, HIGH);
  digitalWrite(SCL_PIN, HIGH);
}

void resumeDisplay(){
  uint8_t command[] = {0xA4};
  sendCommand(command, 1);
}

void displayON(){
  uint8_t command[] = {0xAF};
  sendCommand(command, 1);
}

void displayOFF(){
  uint8_t command[] = {0xAE};
  sendCommand(command, 1);
}

void allPixelsOn(){
  uint8_t command[] = {0xA5};
  sendCommand(command, 1);
}

void displayMode(){
  uint8_t command[] = {0xA4};
  sendCommand(command, 1);
}

void normalDisplay(){
  uint8_t command[] = {0xA6};
  sendCommand(command, 1);
}

void invertDisplay(){
  uint8_t command[] = {0xA7};
  sendCommand(command, 1);
}

void setContrast(uint8_t contrast){
  uint8_t command[] = {0x81, contrast};
  sendCommand(command, 2);
}

void sendCommand(uint8_t * dataStream, uint8_t size){
  digitalWrite(SDA_PIN, LOW);   //Start condition
  delayMicroseconds(1);
  digitalWrite(SCL_PIN, LOW); 
  delayMicroseconds(1);

  sendByte(0x78);               //slave address
  sendByte(0x00);
  for(uint8_t i = 0; i < size; i++){
    sendByte(dataStream[i]);
  }

  digitalWrite(SDA_PIN, LOW);   //Stop condition
  delayMicroseconds(1);
  digitalWrite(SCL_PIN, HIGH);
  delayMicroseconds(1);
  digitalWrite(SDA_PIN, HIGH);
}

void sendData(uint8_t* dataStream, uint8_t size){
  digitalWrite(SDA_PIN, LOW);   //Start condition
  delayMicroseconds(1);
  digitalWrite(SCL_PIN, LOW); 
  delayMicroseconds(1);

  sendByte(0x78);               //slave address
  sendByte(0x40);
  for(uint8_t i = 0; i < size; i++){
    sendByte(dataStream[i]);
  }

  digitalWrite(SDA_PIN, LOW);   //Stop condition
  delayMicroseconds(1);
  digitalWrite(SCL_PIN, HIGH);
  delayMicroseconds(1);
  digitalWrite(SDA_PIN, HIGH);
}

void latchBit(){
  delayMicroseconds(1);
  digitalWrite(SCL_PIN, HIGH);  
  delayMicroseconds(1);
  digitalWrite(SCL_PIN, LOW);
}

void sendByte(uint8_t byte){
  uint8_t buffer;
  uint8_t mask = 0x80;
  for(uint8_t i = 0; i < 8; i++){
    buffer = byte & mask;
    if(buffer != 0){
      digitalWrite(SDA_PIN, HIGH);      
    }else{
      digitalWrite(SDA_PIN, LOW);
    }
    latchBit();
    mask >>= 1;
  }
  checkACK();
}

bool checkACK(){
  uint8_t ACK;
  pinMode(SDA_PIN, INPUT);
  delayMicroseconds(1);
  digitalWrite(SCL_PIN, HIGH);      //Latch bit
  delayMicroseconds(1);
  ACK = digitalRead(SDA_PIN);
  delayMicroseconds(1);
  digitalWrite(SCL_PIN, LOW);
  pinMode(SDA_PIN, OUTPUT);
  if(ACK > 0){ return false; }
  else { return true; }
}