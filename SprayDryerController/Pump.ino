#define pumpP -0.1
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
  } else {
    killPump();
  }

}

void killPump() {
  analogWrite(pumpRelay, 0);
}

void resetPumpPID() {
  pumpPID.reset();
}
