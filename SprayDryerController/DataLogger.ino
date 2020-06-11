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
  // TODO: ensure that the filename is only 8 characters long
  String startingTimestamp = "" + currentTime.year() + '.' + currentTime.month() + '.' + currentTime.day() + '.' + currentTime.hour() + '.' + currentTime.minute() + '.' + currentTime.second();
  logFile = SD.open(startingTimestamp + ".log", FILE_WRITE);
  if (logFile) {
    logFile.println("Process Started At:" + startingTimestamp);
    logFile.print("Timestamp\tInput T\tInput Setpoint\tCoil Dutycycle\tOutput T\tOutput Setpoint\tPump Dutycycle\tElapsed Time");
    writeLog();
  } else {
    alarmActive = true;
    writeAlarm("    Data Logger     ");
  }
}

void endLog() {
  if (logFile) {
    logFile.println("log closed normally");
    logFile.close();
  } else {
    alarmActive = true;
    writeAlarm("    Data Logger     ");
  }
}

void writeLog() {
  if (logFile) {
    logFile.print("" + currentTime.hour() + '.' + currentTime.minute() + '.' + currentTime.second());
    logFile.print("\t");
    logFile.print(inputT);
    if (manualHeatPressed) {
      logFile.print("\tManual");
    } else {
      logFile.print("\t");
      logFile.print(inputSetpoint);
    }
    logFile.print("\t");
    logFile.print(CD);
    logFile.print("\t");
    logFile.print(outputT);
    if (manualPumpPressed){
      logFile.print("\tManual");
    }else{
      logFile.print("\t");
      logFile.print(outputSetpoint);
    }
    logFile.print("\t");
    logFile.print(PD);
    logFile.print("\t");
    logFile.println(elapsedTime);
    lastLog = millis();
  } else {
    alarmActive = true;
    writeAlarm("    Data Logger     ");
  }
}

void logData(){
  if(millis()-lastLog >= logInterval){  // Only write a log when the interval has passed
    writeLog();
  }
}
