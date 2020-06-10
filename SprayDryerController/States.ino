void updateState() {
  switch (state) {
    case 0: // Default state - no process is running
      writeLogo();
      break;
    case 1: // Input T setpoint state
      potValue = analogRead(coilPot);
      inputSetpoint = map(potValue, 0, 1023, 100, 300);
      writeLogo();
      writeInputTSetpoint();
      break;
    case 2: // Output T setpoint state
      potValue = analogRead(pumpPot);
      outputSetpoint = map(potValue, 0, 1023, 20, 150);
      writeLogo();
      writeOutputTSetpoint();
      break;
    case 3:  // Warm-up state
      if (manualHeatPressed) {
        manualSetCoil();
      } else {
        PIDSetCoil();
      }
      if (inputT < inputSetpoint + 1 & inputT > inputSetpoint - 1) {
        state = 4;
      }
      writeLogo();
      writeTemps();
      writeTimer();
      logData();
      break;
    case 4:  // Running state
      if (manualHeatPressed) {
        manualSetCoil();
      } else {
        PIDSetCoil();
      }
      if (!idlePressed) {  // Only run the pump if idle is up
        if (manualPumpPressed) {
          manualSetPump();
        } else {
          PIDSetPump();
        }
      }
      writeLogo();
      writeTemps();
      writeTimer();
      logData();
      break;
    case 5:  // Cooldown state
      if (!idlePressed) {  // Only run the pump if idle is up
        if (manualPumpPressed) {
          manualSetPump();
        } else {
          PIDSetPump();
        }
      }
      writeLogo();
      writeTemps();
      writeTimer();
      logData();
      if (inputT - outputT < 10) { // End the process
        endLog();
        if (!alarmActive) {
          clearLCD();
        }
        //TODO: Some friendly finished alarm
        state = 0;
      }
      break;
  }
}

void checkAlarms() {
  if (alarmActive) {
    //TODO: Code to check for alarms and sound the buzzer
  }
}

void updateTimer() {
  elapsedTime = (millis() - timerStart) / 1000;
}
