#include "Globals.h"

void setup() {
  setupLCD();
  setupPins();
  setupTDisplays();
  setupRTC();
}

void loop() {
  // These methods update state variables and run every loop
  readButtons();
  readTemps();
  printTemps();
  // This method handles the functions that depend on the current state
  updateState();
  updateBuzzer();
  updateTimer();
}

void setupPins(){
  pinMode(timerPin, INPUT_PULLUP);
  pinMode(alarmClearPin, INPUT_PULLUP);
  pinMode(startPin, INPUT_PULLUP);
  pinMode(stopPin, INPUT_PULLUP);
  pinMode(idlePin, INPUT_PULLUP);
  pinMode(manualHeatPin, INPUT_PULLUP);
  pinMode(manualPumpPin, INPUT_PULLUP);
  pinMode(SSPin, OUTPUT);
  pinMode(pumpRelay, OUTPUT);
  pinMode(coilRelay, OUTPUT);
  pinMode(alarmBuzzerPin, OUTPUT);
  pinMode(alarmLEDPin, OUTPUT);
  lastPress = millis();
}
