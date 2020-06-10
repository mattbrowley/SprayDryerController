#include "LedControl.h"
#define inputDisplay 0
#define outputDisplay 1

LedControl TDisplays=LedControl(TLEDDA,TLEDCK,TLEDCS,2);  // The 2 is because we have 2 drivers cascaded

void setupTDisplays(){
  // Wake up the MAX7219 drivers from power-saving mode
  TDisplays.shutdown(inputDisplay,false);
  TDisplays.shutdown(outputDisplay,false);
  // Limit each driver to 4 digits
  TDisplays.setScanLimit(inputDisplay, 4);
  TDisplays.setScanLimit(outputDisplay, 4);
  // Set the brightness to a high value (15 is maximum)
  TDisplays.setIntensity(inputDisplay,11);
  TDisplays.setIntensity(outputDisplay,11);
  // and clear the display 
  TDisplays.clearDisplay(inputDisplay);
  TDisplays.clearDisplay(outputDisplay);
}
void printTemps(){
  int value = inputT;
  TDisplays.setDigit(inputDisplay,0,'C',false); // Display "C"
  TDisplays.setDigit(inputDisplay,1,(byte)value%10,false); // Display the ones place
  value = value / 10;
  TDisplays.setDigit(inputDisplay,2,(byte)value%10,false); // Display the tens place
  value = value / 10;
  TDisplays.setDigit(inputDisplay,3,(byte)value%10,false); // Display the hundreds place
  value = outputT;
  TDisplays.setDigit(outputDisplay,0,'C',false); // Display "C"
  TDisplays.setDigit(outputDisplay,1,(byte)value%10,false); // Display the ones place
  value = value / 10;
  TDisplays.setDigit(outputDisplay,2,(byte)value%10,false); // Display the tens place
  value = value / 10;
  TDisplays.setDigit(outputDisplay,3,(byte)value%10,false); // Display the hundreds place
} 
