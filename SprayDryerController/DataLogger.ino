#include <SD.h>
#include "RTClib.h"

RTC_DS1307 rtc;
DateTime currentTime = rtc.now();
File logFile;

void setupRTC() {
  rtc.begin();
  if (! rtc.isrunning()) {
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void setupSD() {
  SD.begin(SDCS);
}

void startLog() {
  if (logFile) { // prior log file is still open
    logFile.println("log failed to close normally: closed at start of next log");
    logFile.close();
  }
  currentTime = rtc.now();
  String filename = "" + currentTime.year() + '.' + currentTime.month() + '.' + currentTime.day() + '.' + currentTime.hour() + '.' + currentTime.minute() + '.' + currentTime.second();
  logFile = SD.open(filename + ".log", FILE_WRITE);
  if (logFile) {
    logFile.println("Process Started At:" + filename);
    logFile.print("Timestamp\tInput T\tInput Setpoint\tCoil Dutycycle\tOutput T\tOutput Setpoint\tPump Dutycycle\tElapsed Time");
    writeLog();
  } else {
    // handle error of log file not opening properly
  }
}

void endLog() {
  if (logFile) {
    logFile.println("log closed normally");
    logFile.close();
  } else {
    // handle error of log file not opening properly
  }
}

void writeLog() {
  if (logFile) {
    logFile.print("" + currentTime.hour() + '.' + currentTime.minute() + '.' + currentTime.second());
//    logFile.print("" + "\t" + inputT);
    if (manualHeatPressed) {
      logFile.print("\tManual");
    } else {
//      logFile.print("" + "\t" + inputSetpoint);
    }
//    logFile.print("\t" + coilDutyCycle + "\t" + outputT);
    if (manualPumpPressed){
      logFile.print("\tManual");
    }else{
//      logFile.print("" + "\t" + outputSetpoint);
    }
//    logFile.println("\t" + pumpDutyCycle + "\t" + elapsedTime);
    lastLog = millis();
  } else {
    // handle error of log file not opening properly
  }
}

void logData(){
  if(millis()-lastLog >= logInterval){  // Only write a log when the interval has passed
    writeLog();
  }
}
