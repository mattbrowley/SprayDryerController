#define pumpP -0.1  // Note that these are negative because the pump PID controller should operate in reverse mode
#define pumpI -0.0003
#define pumpD -0.0001

AutoPID pumpPID(&outputT, &outputSetpoint, &pumpDutyCycle, 0, 255, pumpP, pumpI, pumpD);

void manualSetPump() {
  if (!pumpAlarm) { // keep the pump turned off if there is an active pump alarm
    int potValue = analogRead(pumpPot);
    pumpDutyCycle = map(potValue, 0, 1023, 0, 255);
    analogWrite(pumpRelay, pumpDutyCycle);
  } else {
    killPump();
  }
}

void PIDSetPump() {
  if (!pumpAlarm) { // keep the pump turned off if there is an active pump alarm
    pumpPID.run();
    analogWrite(pumpRelay, pumpDutyCycle);
  } else {
    killPump();
  }
}

void killPump() {
  digitalWrite(pumpRelay, LOW);
}

void resetPumpPID() {
  pumpPID.reset();
}
