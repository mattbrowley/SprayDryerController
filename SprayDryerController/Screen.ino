#include <LiquidCrystal_I2C.h>
#define LCD_Address 0x27 // The I2C address for the 20x4 LCD

const uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
const uint8_t smile[8] = {0x0,0xa,0xa,0xa,0x0,0x11,0xe};
const byte topLeft[] = {0x1F,0x1F,0x18,0x18,0x18,0x18,0x18,0x19};
const byte topRight[] = {0x1F,0x1F,0x07,0x0F,0x0F,0x1B,0x1B,0x13};
const byte bottomLeft[] = {0x19,0x1B,0x1B,0x1E,0x1E,0x1C,0x1F,0x1F};
const byte bottomRight[] = {0x13,0x03,0x03,0x03,0x03,0x03,0x1F,0x1F};
const byte degree[] = {0x07,0x05,0x07,0x00,0x00,0x00,0x00,0x00};


LiquidCrystal_I2C lcd(LCD_Address, 20, 4);

void setupLCD(){  
  lcd.init(); 
  lcd.backlight(); // Turn on the backlight
  lcd.createChar(0, topLeft);
  lcd.createChar(1, topRight);
  lcd.createChar(2, bottomLeft);
  lcd.createChar(3, bottomRight);
  lcd.createChar(4, degree);
}

void writeTemps(){
  lcd.setCursor(0,2);
  lcd.print("ISet: ");
  lcd.print(inputSetpoint);
  lcd.print(" CDuty: ");
  lcd.println(coilDutyCycle);
  lcd.print("OSet: ");
  lcd.print(outputSetpoint);
  lcd.print(" PDuty: ");
  lcd.println(pumpDutyCycle);
}

void writeInputTSetpoint(){
  lcd.setCursor(0,2);
  lcd.println("Input T Setpoint:");
  lcd.print(inputSetpoint);
  lcd.write(4); // degree symbol
  lcd.print("C   ");
}

void writeOutputTSetpoint(){
  lcd.setCursor(0,2);
  lcd.println("Output T Setpoint:");
  lcd.print(outputSetpoint);
  lcd.write(4); // degree symbol
  lcd.print("C   ");
}

void writeLogo(){
  if(!alarmActive){
  lcd.setCursor(0,0);
  lcd.write(0); // topLeft of logo
  lcd.write(1); // topRight of logo
  lcd.println(" Division By Zero  ");
  lcd.write(2); // bottomLeft of logo;
  lcd.write(3); //bottomRight of logo;
  lcd.println(" Development Labs  ");
  }
}

void writeAlarm(String message){
  lcd.setCursor(0,0);
  lcd.println("       Alarm!       ");
  lcd.print(message);
  lcd.println("                ");
}
