void readButtons() {
  if (millis() > lastPress + debounceDelay | millis() <  lastPress) { // Debounce time has passed
    readTimer();
    readAlarmClear();
    readStart();
    readStop();
    readIdle();    
    readManualHeat();
    readManualPump();
  }
}

void readTimer() {
  if (!digitalRead(timerPin)) { // The Timer button is currently pressed
    if (!timerPressed) { // The Timer button was not previously pressed
      timerPressed = true;
      lastPress = millis();  // Reset the debounce timer
      // TODO: code for when Timer is pressed
    }
  } else if (timerPressed) { // Timer button released
    timerPressed = false;
    lastPress = millis(); // Reset the debouce timer
  }
}

void readAlarmClear() {
  if (!digitalRead(alarmClearPin)) { // The alarmClear button is currently pressed
    if (!alarmClearPressed) { // The alarmClear button was not previously pressed
      alarmClearPressed = true; 
      lastPress = millis();  // Reset the debounce timer
      if(alarmActive){
        alarmActive = false;
      }
    }
  } else if (alarmClearPressed) {  // alarmClear button released
    alarmClearPressed = false;
    lastPress = millis(); // Reset the debouce timer
  }
}

void readStart() {
  if (!digitalRead(startPin)) { // The start button is currently pressed
    if (!startPressed) { // The start button was not previously pressed
      startPressed = true; 
      lastPress = millis();  // Reset the debounce timer
      if (state < 3){
        state = state + 1;
      }
    }
  } else if (startPressed) {  // start button released
    startPressed = false;
    lastPress = millis(); // Reset the debouce timer
  }
}

void readStop() {
  if (!digitalRead(stopPin)) { // The stop button is currently pressed
    if (!stopPressed) { // The stop button was not previously pressed
      stopPressed = true; 
      lastPress = millis();  // Reset the debounce timer
      if(state == 4){
        killCoil();
        state = 5;
      }
    }
  } else if (stopPressed) {  // stop button released
    stopPressed = false;
    lastPress = millis(); // Reset the debouce timer
  }
}

void readIdle() {
  if (!digitalRead(idlePin)) { // The idle button is currently pressed
    if (!idlePressed) { // The idle button was not previously pressed
      idlePressed = true;  
      lastPress = millis();  // Reset the debounce timer
      killPump();
    }
  } else if (idlePressed) {  // idle button released
    idlePressed = false;
    lastPress = millis(); // Reset the debouce timer
  }
}

void readManualHeat() {
  if (!digitalRead(manualHeatPin)) { // The manualHeat button is currently pressed
    if (!manualHeatPressed) { // The manualHeat button was not previously pressed
      manualHeatPressed = true;  //
      lastPress = millis();  // Reset the debounce timer
      // TODO: code for when manualHeat is pressed
    }
  } else if (manualHeatPressed) {  // manualHeat button released
    manualHeatPressed = false;
    lastPress = millis(); // Reset the debouce timer
  }
}

void readManualPump() {
  if (!digitalRead(manualPumpPin)) { // The manualPump button is currently pressed
    if (!manualPumpPressed) { // The manualPump button was not previously pressed
      manualPumpPressed = true;  //
      lastPress = millis();  // Reset the debounce timer
      // TODO: code for when manualPump is pressed
    }
  } else if (manualPumpPressed) {  // manualPump button released
    manualPumpPressed = false;
    lastPress = millis(); // Reset the debouce timer
  }
}