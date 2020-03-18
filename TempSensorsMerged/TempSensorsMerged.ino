#include <OneWire.h>

#include <LiquidCrystal.h>
#define OneWirePin D6

OneWire DS1820(OneWirePin);

const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5; //mention the pin names to with LCD is connected to
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //Initialize the LCD

int searchAgain = 0;

int led = D5;           // the PWM pin the LED is attached to
int brightness = 120;    // how bright the LED is
int fadeAmount = 10;    // how many points to fade the LED by
int t =1;             // just a counter
int dt = 5000;         // delay time in the loop

// Rotary Encoder Inputs
#define CLK D0
#define DT D1

#define PUSH D2

int counter = 0;
int currentStateCLK;
int lastStateCLK;
int currentStateDT;
String currentDir ="";
String menuItems[3] = { "1. Change ID       ", "2. Measure       ", "3. Brightness      " };
String clearLine = "                ";
int currentMenu = 0;
byte address[8];

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long lastMicros = 0;
unsigned long debounceDelay = 1;    // the debounce time; increase if the output flickers
unsigned long LastPushTime = 0;     // to check for double clicks
unsigned long DC_Delay = 1000;     // maximum delay for double clicks

bool found = false;
bool detect = false;

bool changingID = false; //state where the ID of current sensor is being changed
bool searchingID = false; //state of searching sensors
bool measuringState = false; //state of searching sensors
bool changingBrightness = false; //state of changing brightness level
bool menuState = true; //state of menu display
bool interrupted = false;

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
  lcd.begin(16, 2);//We are using a 16*2 LCD
  pinMode(OneWirePin,OUTPUT);
  // Set encoder pins as inputs
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  pinMode(PUSH,INPUT);

  // Setup Serial Monitor
  Serial.begin(250000);

  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);

  lastDebounceTime = millis();
  lastMicros = micros();
  
  // Call updateEncoder() when any high/low changed seen
  // on interrupt 0 (pin 2), or interrupt 1 (pin 3)
  attachInterrupt(CLK, updateEncoder, CHANGE);
  attachInterrupt(DT, updateEncoder, CHANGE);
  attachInterrupt(PUSH, updateEncoder, CHANGE);
  
  analogWrite(led, brightness); // initial brightness level
  
  resolutionSet();
  lcd.setCursor(0, 0); //At first row first column
  lcd.print("------MENU------");
  lcd.setCursor(0, 1); //At second row first column
  lcd.print(menuItems[currentMenu]);
  
}

// the loop routine runs over and over again forever:
void loop() {  
  if(searchAgain == 1){
    searchAgain = 0;
    lookUpSensors();
  }  
  checkStates();
//  t++;
}

void checkStates(){
  interrupted = false;
  if(menuState){
    menuStateLoop();
  }
  else if(searchingID){
    searchingIDLoop();
  }
  else if(changingID) {
    changingIDLoop();
  }
  else if(measuringState){
    measuringStateLoop();
  } 
  else if(changingBrightness){
    changingBrightnessLoop();
  }
  else{
    Serial.println("Unknown state!");
  }
//  printStates();
}

void printStates(){
  Serial.print("menuState ");
  Serial.println(menuState);  
  Serial.print("searchingID ");
  Serial.println(searchingID); 
  Serial.print("changingID ");
  Serial.println(changingID); 
  Serial.print("measuringState ");
  Serial.println(measuringState); 
  Serial.print("changingBrightness ");
  Serial.println(changingBrightness);  
}

void menuStateLoop(){
  lcd.setCursor(0, 1); //At second row first column
  lcd.print(menuItems[currentMenu]);
  delayLoop();  
}

void searchingIDLoop(){
  lcd.setCursor(0, 1); //At second row first column
  lcd.print("Rotate-next ID  ");
  delayLoop();  
  lcd.setCursor(0, 1); //At second row first column
  lcd.print("Push-change ID  ");
  delayLoop();
}

void changingIDLoop(){
//  lcd.setCursor(0, 1); //At second row first column
//  lcd.print("Rotate-change   ");
//  delayLoop();
  lcd.setCursor(0, 1); //At second row first column
  lcd.print("Push-confirm ID ");
  delayLoop();    
}

void measuringStateLoop(){
  lcd.setCursor(0, 1); //At second row first column
  lcd.print("Rotate-next ID  ");
  delayLoop(); 
  lcd.setCursor(0, 1); //At second row first column
  lcd.print("Push-Measure    ");
  delayLoop(); 
}

void changingBrightnessLoop(){
  lcd.setCursor(0, 0); //At first row first column
  lcd.print("Brightness level");
  lcd.setCursor(0, 1); //At second row first column
  lcd.print("Rotate - change ");
  delayLoop(); 
  lcd.setCursor(0, 1); //At second row first column
  lcd.print("Push - Exit     ");
  delayLoop(); 
}

void delayLoop(){
  for (int i = 0; i<dt; i++){
    if(interrupted){
      break;
    }
    delay(1); 
  }
}

void resolutionSet()
{
  while(DS1820.search(address))
  {
    byte data[12];
    byte copied = 0x00;
    readSratchpad(&data[0], address);
    /* resolution bit for 9 bit: 0x1F, 10 bit: 0x3F, 11 bit: 0x5F, 12 bit: 0x7F,   */
    data[4] = 0x7F;
    DS1820.reset();
    DS1820.select(address);
    DS1820.write(0x4E, 1); //Write data into scratchpad
    DS1820.write(data[2], 1); //write LSB of ID to User byte 1 of sensor
    DS1820.write(data[3], 1); //write MSB of ID to User byte 2 of sensor
    DS1820.write(data[4], 1); //write configuration bit of sensor
    DS1820.reset();
    DS1820.select(address);
    DS1820.write(0x48, 1); //Copy sratchpad contents to non volatile memory
    while(!DS1820.read()){
      Serial.println("waiting for copying resolution bit to sensor");
    }
    copied = DS1820.read();
    if(copied){
      Serial.println("Resolution changed");
    }
  }
}

void mainMenuState()
  {
  lcd.clear();
  lcd.setCursor(0, 0); //At first row first column
  lcd.print("------MENU------");
  lcd.setCursor(0, 1); //At second row first column
  lcd.print(menuItems[currentMenu]);
  changingID = false; 
  searchingID = false; 
  measuringState = false; 
  changingBrightness = false; 
  menuState = true; 
}
  
void lookUpSensors()
  {
  found = false;
  detect = false;
 
  Serial.println("Searching for next sensor");
  DS1820.search(address); //search for next sensor
  switch (address[0])
    {
    case 0x10:
      Serial.print("DS18S20: ");  // oder alter DS1820
      detect = true;
      break;
    case 0x28:
      Serial.print("DS18B20: ");
      detect = true;
      break;
    case 0x22:
      Serial.print("DS1822: ");
      detect = true;
      break;
    default:
      Serial.println("Device ist not a DS18x20-Sensor.");
    } 
  // Adresse anzeigen, wenn ein Temperatursensor gefunden wurde
  if (detect)
    {
    found = true;
    showAddress(address);
    showID(address);
    } // ... if detect
  if (!found)
    { Serial.println("No sensors found!");
      lcd.setCursor(0, 0); //At secound row first column
      lcd.print("No sensor");
    }
  }

void readSratchpad(byte *data, byte address[8])
{
  DS1820.reset();
  DS1820.select(address);
  DS1820.write(0xBE); //to read data from scratchpad
  Serial.println("Reading from scratchpad: "); 
  for(byte i=0;i<9;i++){
    data[i] = DS1820.read();
    if (data[i] <= 0xF){
      Serial.print("0");
      }
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.println(""); 
  Serial.print("CRC = ");
  Serial.println(OneWire::crc8(data, 8), HEX);
}
   
void showAddress(byte address[8])
  {
  // Im Array address enthaltene Daten kompakt sedezimal ausgeben
  byte i;

  if (OneWire::crc8(address, 7) != address[7])
    { Serial.println("No valid CRC!"); 
    }
  else
    {
    //alles ist ok, anzeigen
    Serial.print("Address: "); 
    for (i = 0; i < 7; i++)
      {
      if (address[i] <= 0xF)
        { Serial.print("0"); }
      Serial.print(address[i],HEX);
      }
    Serial.println("");
    }
  }

void showID(byte address[8])
{
  byte data[12];
  int ID;
  readSratchpad(&data[0], address);
  Serial.print("ID of the sensor: ");
  ID = data[3];
  ID = (ID<<8) + data[2];
  Serial.println(ID, DEC);
  lcd.clear();
  lcd.setCursor(0, 0); //At first row first column
  lcd.print("Sensor ID: ");
  lcd.print(String(ID,DEC));
}

void changeID()
{
  byte copied = 0x00;
  byte data[12];
  int ID = counter; // ID to be written to sensor
  byte IDhex[2];
  IDhex[0] = lowByte(ID);
  IDhex[1] = highByte(ID); 
  int newID; // to check if correct ID is saved in sensor after writing
  DS1820.reset();
  DS1820.select(address);
  DS1820.write(0x4E, 1); //Write data into scratchpad
  DS1820.write(IDhex[0], 1); //write LSB of ID to User byte 1 of sensor
  DS1820.write(IDhex[1], 1); //write MSB of ID to User byte 2 of sensor
  DS1820.reset();
  DS1820.select(address);
  DS1820.write(0x48, 1); //Copy ID in sratchpad to non volatile memory
  while(!DS1820.read()){
    Serial.println("waiting for copying ID to sensor");
  }
  copied = DS1820.read();
  if(copied){
    Serial.println("Copied ID to sensor");
    readSratchpad(&data[0], address);
    Serial.print("New ID added to sensor: ");
    newID = data[3];
    newID = (newID<<8) + data[2];
    Serial.println(newID, DEC);
    lcd.clear();
    lcd.setCursor(0, 0); //At first row first column
    lcd.print("New ID: ");
    lcd.print(String(newID,DEC));
    lcd.setCursor(0, 1); //At second row first column
    lcd.print("Rotate-search");
  }
  else{
    Serial.print("Not copied: ");
    Serial.print(IDhex[0], HEX);
    Serial.print(" ");
    Serial.print(IDhex[1], HEX);
    Serial.println(copied, HEX);
  }
  changingID = false;
  searchingID = true;
}

void measure()
{
  byte converted = 0x00;
  int ID;
  byte data[12];
  float temp;
  DS1820.reset();
  DS1820.select(address);
  DS1820.write(0x44, 1); //Convert Temperature
  while(!DS1820.read()){
    Serial.print(".");
  }
  converted = DS1820.read();
  if(converted){
    Serial.println("Converted by sensor");
    readSratchpad(&data[0], address);
    
    // temperature conversion
    byte sign = data[1] & 0x80;
    int T = (data[1]<<8) + data[0];
    if(sign){
      // 2's compliment
      T = ((T^0xFFFF)+1)*-1;
    }
    Serial.print("T value");
    Serial.println(T);
    temp = (float)T/16.0;
    
    Serial.print("Temperature: ");
    Serial.println(temp);
    ID = data[3];
    ID = (ID<<8) + data[2];
    lcd.clear();
    lcd.setCursor(0, 0); //At first row first column
    lcd.print("ID ");
    lcd.print(String(ID,DEC));
    lcd.print(":");
    lcd.print(temp);
    lcd.print((char)223);
    lcd.print("C");    
  }
}

void menuStatePush(){
    if(currentMenu == 0){
    Serial.println("Changing ID menu selected");
    searchingID = true;
    changingID = false;
    measuringState = false;
    changingBrightness = false;
    menuState = false;
    lookUpSensors();
  }
  if(currentMenu == 1){
    Serial.println("Measurement menu selected");
    searchingID = false;
    changingID = false;
    measuringState = true;
    changingBrightness = false;
    menuState = false;
    lookUpSensors();
  }
  if(currentMenu == 2){
    Serial.println("Changing brightness menu selected");
    searchingID = false;
    changingID = false;
    measuringState = false;
    changingBrightness = true;
    menuState = false;
    counter = brightness;
  }
}

void searchingIDPush(){
  Serial.println("Pushed to change ID of current sensor");
  lcd.clear();
  lcd.setCursor(0, 0); //At first row first column
  lcd.print("Change to: ");
  counter = 0;
  lcd.print(String(counter,DEC));
  searchingID = false;
  changingID = true;
}

void menuStateRotation(){
  Serial.println("Printing next menu item");
  // the encoder is rotating CCW
  if (currentStateDT != currentStateCLK) {
    currentMenu --;
    if(currentMenu<0){
      currentMenu = 2;
      }            
  }
  else{
    currentMenu ++;
    if(currentMenu>2){
      currentMenu = 0;
      }
  }
  // Remember last CLK state
  lastStateCLK = currentStateCLK;
}

void changingIDRotation(){
  // the encoder is rotating CCW so decrement
  if (currentStateDT != currentStateCLK) {
    if(counter>0){
      counter --;
    }
    currentDir ="CCW";  
  } 
  else {
    // Encoder is rotating CW so increment
    counter ++;
    currentDir ="CW";
  }
  Serial.print("Counter: ");
  Serial.println(counter);
  Serial.println(currentDir);
  lcd.clear();
  lcd.setCursor(0, 0); //At first row first column
  lcd.print("Change to: ");
  lcd.print(String(counter,DEC));
  // Remember last CLK state
  lastStateCLK = currentStateCLK;
}

void changingBrightnessRotation(){
  // the encoder is rotating CCW so decrement
  if (currentStateDT != currentStateCLK) {
    if(counter >= fadeAmount){
      counter = counter - fadeAmount;
    }
    currentDir ="CCW";  
  } 
  else {
    // Encoder is rotating CW so increment
    if(counter <= 255 - fadeAmount){
      counter = counter + fadeAmount;
    }
    currentDir ="CW";
  }
  Serial.print("Counter: ");
  Serial.println(counter);
  analogWrite(led, counter);
  // Remember last CLK state
  lastStateCLK = currentStateCLK;
}

void checkPush(){
  Serial.print("LastPushTime ");
  Serial.println(LastPushTime);
  Serial.print("millis - LastPushTime ");
  Serial.println(millis() - LastPushTime);
  if(millis() - LastPushTime < DC_Delay)  // double click
  {
    lastDebounceTime = millis();
    LastPushTime = millis();  
    mainMenuState(); // return to main menu  
  }
  else{   // normal push
    lastDebounceTime = millis();
    LastPushTime = millis();
    if(menuState){
      menuStatePush();
    }
    else if(searchingID){
      searchingIDPush();
    }
    else if(changingID){
      Serial.print("Changing ID of current sensor to: ");
      Serial.println(counter);
      changeID();
    }
    else if(measuringState){
      Serial.println("Measuring Temp of current sensor: ");
      measure();
    }
    else if(changingBrightness){
      Serial.println("Returning to main menu: ");
      mainMenuState();
    }
  }
  // Remember last CLK state
  lastStateCLK = currentStateCLK;
}

void updateEncoder(){
  // Read the current state of CLK
  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    interrupted = true;
    if(digitalRead(PUSH)) // Encoder push
    {
      checkPush();
    }
       
    else // Encoder rotation
    {   
      lastDebounceTime = millis();
      currentStateCLK = digitalRead(CLK);
      currentStateDT = digitalRead(DT);
  
      // If last and current state of CLK are different, then pulse occurred
      // React to only 1 state change to avoid double count
      if (currentStateCLK != lastStateCLK  && currentStateCLK == 1)
      {
        Serial.println("Rotated");
        if(menuState){
          menuStateRotation();
        }        
        if(searchingID){
          Serial.println("Search for other sensors");
          searchAgain = 1;
        } 
        if(changingID){
          changingIDRotation();
        }
        if(measuringState){
          lookUpSensors();
        }
        if(changingBrightness){
          changingBrightnessRotation();
        }       
      }
        lastMicros = micros();    
    }
    // Remember last CLK state
    lastStateCLK = currentStateCLK;
  }
}
