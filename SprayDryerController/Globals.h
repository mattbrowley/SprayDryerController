#ifndef Globals_h
#define Globals_h

#include "Arduino.h"

//TODO: Choose sane pin numbers
#define SCL 19  // I2C bus
#define SDA 18  // I2C bus
#define SCK 13  // SPI bus
#define MISO 12  // SPI bus
#define MOSI 11  // SPI bus
#define ITCS 10  // SPI bus: input thermocouple chip select
#define OTCS 9  // SPI bus: output thermocouple chip select
#define CTCS 8  // SPI bus: heating coil thermocouple chip select
#define SDCS  6 // SPI bus: SD-card chip select pin
#define SSPin 5 // SPI bus slave select pin -- must be set to output mode
#define TLEDCS 7 // TDisplay bus: Temperature displays chip select
#define TLEDDA 6 // TDisplay bus: Data line
#define TLEDCK 5 // TDisplay bus: Clock
#define pumpPot A0 // Potentiometer for control of the pump motor speed
#define pumpRelay 2 // PWM output pin for the pump motor relay
#define coilPot A1 // Potentiometer for control of the heating coil
#define coilRelay 2 // PWM output pin for the coil relay
#define timerPin 7  // Button for starting the timer
#define alarmClearPin 2  // Button to clear alarms
#define startPin 4  // Button to begin a process
#define stopPin 3  // Button to end a process
#define idlePin 6  // Toggle to enter idle mode
#define manualHeatPin 5  // Toggle to control the heating coil manually
#define manualPumpPin 4 // Toggle to control the pump manually
#define alarmBuzzerPin 3 // Buzzer for an alarm
#define alarmLEDPin 3 // Bright LED to signal an alarm

#define maxCoilT 600 // Maximum allowed temperature for the heating coil

#define debounceDelay 100  // Buttons aren't queried in the 0.1 s after a button state change
#define logInterval 5000  // log data every 5 seconds while a process is running

float inputT;  // Input Temperature
float inputCJT;  // Input Cold Junction Temperature (breakout board temperature)
float inputSetpoint = 0; // Setpoint for the input temperature
float outputT;  // Output Temperature
float outputCJT;  // Output Cold Junction Temperature (breakout board temperature)
float outputSetpoint = 0; // Setpoint for the output temperature
float coilT;  // Heating Coil Temperature
float coilCJT;  // Heating Coil Cold Junction Temperature (breakout board temperature)
int coilDutyCycle = 0;
int pumpDutyCycle = 0;
int elapsedTime = 0;

int state = 0; // Which state the controller is currently in
unsigned long lastPress;  // Timestamp used for software debouncing of buttons
unsigned long timerStart;  // Timestamp used for counting seconds since the timer starts
unsigned long lastLog;  // Timestamp used to log data at 5 second intervals
bool timeStarted = false;
bool timerPressed = false;
bool alarmClearPressed = false;
bool startPressed = false;
bool stopPressed = false;
bool idlePressed = false;
bool manualHeatPressed = false;
bool manualPumpPressed = false;
int potValue; // Temporary variable to store raw potentiometer analogRead values
bool alarmActive = false;
#endif
