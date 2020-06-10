void manualSetPump(){
  int potValue = analogRead(pumpPot);
  pumpDutyCycle = map(potValue, 0, 1023, 0, 255);
  analogWrite(pumpRelay, pumpDutyCycle);
}

void PWMSetPump(){
  
}

void killPump(){
  analogWrite(pumpRelay, 0);
}
