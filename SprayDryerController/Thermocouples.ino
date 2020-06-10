#include <SparkFunMAX31855k.h>

SparkFunMAX31855k inputTProbe(ITCS);
SparkFunMAX31855k outputTProbe(OTCS);
SparkFunMAX31855k coilTProbe(CTCS);

void readTemps(){
  readInputT();
  readOutputT();
  readCoilT();
}

void readInputT(){
  inputT = inputTProbe.readTempC();
  if (isnan(inputT)){ // input temperature probe returned an error
    // Handle error
  }
}

void readInputCJT(){
  inputCJT = inputTProbe.readCJT();
  if (isnan(inputCJT)){ // input temperature probe returned an error
    // Handle error
  }
}

void readOutputT(){
  outputT = outputTProbe.readTempC();
  if (isnan(outputT)){ // output temperature probe returned an error
    // Handle error
  }
}

void readOutputCJT(){
  outputCJT = outputTProbe.readCJT();
  if (isnan(outputCJT)){ // output temperature probe returned an error
    // Handle error
  }
}

void readCoilT(){
  coilT = coilTProbe.readTempC();
  if (isnan(coilT)){ // coil temperature probe returned an error
    // Handle error
  }
  if (coilT >= maxCoilT){
    alarmActive = true;
    writeAlarm("   Max Coil Temp    ");
  }
}

void readCoilCJT(){
  coilCJT = coilTProbe.readCJT();
  if (isnan(coilCJT)){ // coil temperature probe returned an error
    // Handle error
  }
}
