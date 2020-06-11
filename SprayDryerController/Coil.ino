#define coilP 0.1
#define coilI 0.0003
#define coilD 0.0001

AutoPID coilPID(&inputT, &inputSetpoint, &coilDutyCycle, 0, 1000, coilP, coilI, coilD);

void manualSetCoil() {
  if (!coilAlarm) { // Keep coil turned off if there is an active coil alarm
    int potValue = analogRead(coilPot);
    coilDutyCycle = map(potValue, 0, 1023, 0, 1000);
    if(millis()%1000 <= coilDutyCycle){ // This creates a slow 1Hz PWM signal
      digitalWrite(coilRelay, HIGH);
    } else{
      digitalWrite(coilRelay, LOW);
    }
  } else {
    killCoil();
  }
}

void PIDSetCoil() {
  if (!coilAlarm) { // Keep coil turned off if there is an active coil alarm
    coilPID.run();
    if(millis()%1000 <= coilDutyCycle){  // This creates a slow 1Hz PWM signal
      digitalWrite(coilRelay, HIGH);
    } else{
      digitalWrite(coilRelay, LOW);
    }
  }
  else {
    killCoil();
  }
}

void killCoil() {
  digitalWrite(coilRelay, LOW);
}

void resetCoilPID() {
  coilPID.reset();
}
