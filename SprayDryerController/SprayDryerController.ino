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
  updateLEDs();
}

void setupPins() {
  pinMode(timerPin, INPUT_PULLUP);
  pinMode(alarmClearPin, INPUT_PULLUP);
  pinMode(startPin, INPUT_PULLUP);
  pinMode(stopPin, INPUT_PULLUP);
  pinMode(idlePin, INPUT_PULLUP);
  pinMode(manualHeatPin, INPUT_PULLUP);
  pinMode(manualPumpPin, INPUT_PULLUP);
  pinMode(pumpRelay, OUTPUT);
  pinMode(coilRelay, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(alarmLEDPin, OUTPUT);
  pinMode(timerLEDPin, OUTPUT);
  pinMode(warmupLEDPin, OUTPUT);
  pinMode(runningLEDPin, OUTPUT);
  pinMode(cooldownLEDPin, OUTPUT);
  pinMode(manualHeatLED, OUTPUT);
  pinMode(manualPumpLED, OUTPUT);
  pinMode(idleLED, OUTPUT);
  lastPress = millis();
}
