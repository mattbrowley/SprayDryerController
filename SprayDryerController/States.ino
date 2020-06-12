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
      if (inputT < inputSetpoint + 1 & inputT > inputSetpoint - 1) { // Input temp has reached setpoint +/- 1
        buzzesRemaining = 4; // Three chirps to indicate end of warmup stage
        outputTReached = false;
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
      if (inputT > inputSetpoint + 10 | inputT < inputSetpoint - 10) { // Input temp has strayed too far
        alarmActive = true;
        writeAlarm("Input T Out Of Range");
      }
      if (outputTReached) {
        if (outputT > outputSetpoint + 10 | outputT < outputSetpoint - 10) { // Output temp has strayed too far
          alarmActive = true;
          writeAlarm("Output T Out Of Range");
        }
      } else {
        if (inputT < inputSetpoint + 1 & inputT > inputSetpoint - 1) { // Output temp has reached setpoint
          outputTReached = true;
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
        killCoil();
        killPump();
        endLog();
        buzzesRemaining = 6;  // 5 chirps to indicate the end of the cooldown phase
        if (!alarmActive) {
          clearLCD();
        }
        state = 0;
      }
      break;
  }
}

void updateBuzzer() {
  if (buzzesRemaining > 0) {
    if (buzzerActive) {
      if (millis() % 1000 >= 500) {
        digitalWrite(buzzerPin, HIGH);
      } else {
        digitalWrite(buzzerPin, LOW);
      }
    } else {
      if (millis() % 1000 < 500) { // This is a bit convoluted, but it ensures an indicator buzz lasts 1/2 second
        buzzerActive = true;
        buzzesRemaining = buzzesRemaining - 1; // You will need to set buzzesRemaining to 1 more than the number of buzzes you actually want
      }
    }
  } else {
    buzzerActive = false;
  }
  if (alarmActive) {
    digitalWrite(buzzerPin, HIGH);
  } else if (!buzzerActive) {
    digitalWrite(buzzerPin, LOW);
  }
}

void updateTimer() {
  if (timerActive) { // Only give nonzero times if the timer has been manually started
    elapsedTime = (millis() - timerStart) / 1000;
  } else {
    elapsedTime = 0;
  }
}

void updateLEDs() {
  if (alarmActive) {
    digitalWrite(alarmLEDPin, HIGH);
  } else {
    digitalWrite(alarmLEDPin, LOW);
  }
  if (timerActive & millis() % 1000 > 500) { // Slowly blinking light while timer is counting
    digitalWrite(timerLEDPin, HIGH);
  } else {
    digitalWrite(timerLEDPin, LOW);
  }
  if (manualHeatPressed) {
    digitalWrite(manualHeatLED, HIGH);
  } else {
    digitalWrite(manualHeatLED, LOW);
  }
  if (manualPumpPressed) {
    digitalWrite(manualPumpLED, HIGH);
  } else {
    digitalWrite(manualPumpLED, LOW);
  }
  if (idlePressed){
    digitalWrite(idleLED, HIGH);
  } else {
    digitalWrite(idleLED, LOW);
  }
  if (state == 3) {
    digitalWrite(warmupLEDPin, HIGH);
    digitalWrite(runningLEDPin, LOW);
    digitalWrite(cooldownLEDPin, LOW);
  } else if (state == 4) {
    digitalWrite(warmupLEDPin, LOW);
    digitalWrite(runningLEDPin, HIGH);
    digitalWrite(cooldownLEDPin, LOW);
  } else if (state == 5) {
    digitalWrite(warmupLEDPin, LOW);
    digitalWrite(runningLEDPin, LOW);
    digitalWrite(cooldownLEDPin, HIGH);
  } else {
    digitalWrite(warmupLEDPin, LOW);
    digitalWrite(runningLEDPin, LOW);
    digitalWrite(cooldownLEDPin, LOW);
  }
}
