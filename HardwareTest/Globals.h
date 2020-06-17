#ifndef Globals_h
#define Globals_h

#include <AutoPID.h>
#include "Arduino.h"

#define SCL 21  // I2C bus
#define SDA 20  // I2C bus
#define SCK 76  // SPI bus  -- These are on the SPI header in the center of the board
#define MISO 74  // SPI bus  -- These are on the SPI header in the center of the board
#define MOSI 75  // SPI bus  -- These are on the SPI header in the center of the board
#define CTCS 14  // SPI bus: input thermocouple chip select
#define ITCS 15  // SPI bus: output thermocouple chip select
#define OTCS 16  // SPI bus: heating coil thermocouple chip select
#define SDCS  17 // SPI bus: SD-card chip select pin
#define buzzerPin 18 // Pin to activate the alarm buzzer
#define TLEDCS 5 // TDisplay bus: Temperature displays chip select
#define TLEDDA 4 // TDisplay bus: Data line
#define TLEDCK 3 // TDisplay bus: Clock
#define pumpPot A1 // Potentiometer for control of the pump motor speed
#define pumpRelay 6 // PWM output pin for the pump motor relay
#define coilPot A0 // Potentiometer for control of the heating coil
#define coilRelay 7 // PWM output pin for the coil relay
#define timerPin 51  // Button for starting the timer
#define timerLEDPin 49 // Indicates that the timer is running
#define alarmClearPin 47  // Button to clear alarms
#define startPin 45  // Button to begin a process
#define stopPin 43  // Button to end a process
#define idlePin 41  // Toggle to enter idle mode
#define idleLED 39 // LED indicator for when the system is in idle mode
#define manualHeatPin 37  // Toggle to control the heating coil manually
#define manualHeatLED 35 // LED indicator for when the heating coil is being controlled manually
#define manualPumpPin 33 // Toggle to control the pump manually
#define manualPumpLED 31 // LED indicator for when the pump is being controlled manually
#define alarmLEDPin 56 // Bright LED to signal an alarm
#define warmupLEDPin 57 // Indicates that the system is in the warmup state
#define runningLEDPin 58 // Indicates that the system is in the running state
#define cooldownLEDPin 59 // Indicates that the system is in the cooldown state

#define maxCoilT 600 // Maximum allowed temperature for the heating coil

#define debounceDelay 100  // Buttons aren't queried in the 0.1 s after a button state change
#define logInterval 5000  // log data every 5 seconds while a process is running

double inputT = 0;  // Input Temperature
double inputCJT = 0;  // Input Cold Junction Temperature (breakout board temperature)
double inputSetpoint = 0; // Setpoint for the input temperature
double outputT = 0;  // Output Temperature
double outputCJT = 0;  // Output Cold Junction Temperature (breakout board temperature)
double outputSetpoint = 0; // Setpoint for the output temperature
double coilT = 0;  // Heating Coil Temperature
double coilCJT = 0;  // Heating Coil Cold Junction Temperature (breakout board temperature)
double coilDutyCycle = 0; // Ranges from 0 (off) to 1000 (on)
double pumpDutyCycle = 0; // Ranges from 0 (off) to 255 (on)
int CD = 0; // Coil duty cycle as a percent
int PD = 0; // Pump duty cycle as a percent
unsigned int elapsedTime = 0;  // Manual timer

int state = 0; // Which state the controller is currently in
unsigned long lastPress = 0;  // Timestamp used for software debouncing of buttons
unsigned long timerStart = 0;  // Timestamp used for counting seconds since the timer starts
unsigned long lastLog = 0;  // Timestamp used to log data at 5 second intervals
bool outputTReached = false;  // used to suppress "out of range" alarms at the beginning of the runnning stage
bool timeStarted = false;
bool timerPressed = false;
bool alarmClearPressed = false;
bool startPressed = false;
bool stopPressed = false;
bool idlePressed = false;
bool manualHeatPressed = false;
bool manualPumpPressed = false;
bool timerActive = false;
int potValue = 0; // Temporary variable to store raw potentiometer analogRead values
bool alarmActive = false;
bool pumpAlarm = false;
bool coilAlarm = false;
bool buzzerActive = false;  // Used in making announcement buzzes
bool loggingActive = false;
int buzzesRemaining = 0; // State changes are announced by a series of buzzes
#endif
