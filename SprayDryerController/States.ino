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
        PWMSetCoil();
      }
      if (inputT < inputSetpoint + 1 & inputT > inputSetpoint - 1) {
        state = 4;
      }
      writeLogo();
      writeTemps();
      logData();
      break;
    case 4:  // Running state
      if (manualHeatPressed) {
        manualSetCoil();
      } else {
        PWMSetCoil();
      }
      if (!idlePressed) {  // Only run the pump if idle is up
        if (manualPumpPressed) {
          manualSetPump();
        } else {
          PWMSetPump();
        }
      }
      writeLogo();
      writeTemps();
      logData();
      break;
    case 5:  // Cooldown state
      logData();
      if (inputT - outputT < 10) {
        endLog();
        //TODO: Some friendly finished alarm
        state = 0;
      }
      break;
    case 6:  // Idle state
      logData();
      break;
  }
}

void checkAlarms(){
  if(alarmActive){
  //TODO: Code to check for alarms and sound the buzzer
  }
}
