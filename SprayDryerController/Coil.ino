void manualSetCoil(){
  int potValue = analogRead(coilPot);
  coilDutyCycle = map(potValue, 0, 1023, 0, 255);
  analogWrite(coilRelay, coilDutyCycle);
}

void PWMSetCoil(){
  
}

void killCoil(){
  analogWrite(coilRelay, 0);
}
