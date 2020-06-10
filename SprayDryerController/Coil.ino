#define coilP 0.1
#define coilI 0.0003
#define coilD 0.0001

AutoPID coilPID(&inputT, &inputSetpoint, &coilDutyCycle, 0, 255, coilP, coilI, coilD);

void manualSetCoil() {
  if (!coilAlarm) { // Keep coil turned off if there is an active coil alarm
    int potValue = analogRead(coilPot);
    coilDutyCycle = map(potValue, 0, 1023, 0, 255);
    analogWrite(coilRelay, coilDutyCycle);
  } else {
    killCoil();
  }
}

void PIDSetCoil() {
  if (!coilAlarm) { // Keep coil turned off if there is an active coil alarm
    coilPID.run();
  }
  else {
    killCoil();
  }
}

void killCoil() {
  analogWrite(coilRelay, 0);
}

void resetCoilPID() {
  coilPID.reset();
}
