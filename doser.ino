/**
 * Author Teemu Mäntykallio
 * Initializes the library and runs the stepper
 * motor in alternating directions.
 */

#include <TMCStepper.h>

#define EN_PIN           7 // Enable
#define DIR_PIN          9 // Direction
#define STEP_PIN         8 // Step
#define CS_PIN           10 // Chip select
#define SERIAL_PORT Serial // TMC2208/TMC2224 HardwareSerial port

#define R_SENSE 0.11f // Match to your driver
                      // SilentStepStick series use 0.11
                      // UltiMachine Einsy and Archim2 boards use 0.2
                      // Panucatt BSD2660 uses 0.1
                      // Watterott TMC5160 uses 0.075

TMC2130Stepper driver(CS_PIN, R_SENSE);

void setup() {
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);      // Enable driver in hardware

                                  // Enable one according to your setup
  SPI.begin();                    // SPI drivers

  driver.begin();                 //  SPI: Init CS pins and possible SW SPI pins
  driver.toff(5);                 // Enables driver in software
  driver.rms_current(900);        // Set motor RMS current
  driver.microsteps(16);          // Set microsteps to 1/16th

  driver.en_pwm_mode(true);       // Toggle stealthChop on TMC2130/2160/5130/5160
  driver.pwm_autoscale(true);     // Needed for stealthChop
}

bool shaft = false;

void loop() {
  // Run 5000 steps and switch direction in software
  for (uint16_t i = 10000; i>0; i--) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(80);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(80);
  }
  shaft = !shaft;
  driver.shaft(shaft);
}
