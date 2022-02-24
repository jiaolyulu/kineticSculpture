/**
 * adapted by Lu Lyu for nano IOT board. https://jiaolyulu.github.io/kineticSculpture/stepper
 * Based on Author Teemu Mäntykallio
 * Initializes the library and runs the stepper
 * motor in alternating directions.
 */

#include <TMCStepper.h>

#define EN_PIN           4 // Enable
#define DIR_PIN          2 // Direction
#define STEP_PIN         3 // Step

#define SERIAL_PORT Serial1 // TMC2208/TMC2224 HardwareSerial port
#define DRIVER_ADDRESS 0b10 // TMC2209 Driver address according to MS1 and MS2
#define interruptPin     9
#define STALL_VALUE 150

#define R_SENSE 0.11f // Match to your driver

TMC2209Stepper driver(&SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);


void setup() {
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), diagnose, CHANGE);
  digitalWrite(EN_PIN, LOW);      // Enable driver in hardware
  Serial.begin(115200);

  SERIAL_PORT.begin(115200);      // HW UART drivers
  //driver.beginSerial(115200);     // SW UART drivers

  driver.begin();                 //  SPI: Init CS pins and possible SW SPI pins
                                  // UART: Init SW UART (if selected) with default 115200 baudrate
  //driver.toff(5);                 // Enables driver in software
  driver.rms_current(1000);        // Set motor RMS current
  driver.microsteps(32);          // Set microsteps to 1/32th

  driver.TCOOLTHRS(0xFFFFF); // TCOOLTHRS: This is the lower threshold velocity for switching on smart energy CoolStep and StallGuard to DIAG output. (unsigned)Set this parameter to disable CoolStep at low speeds, where it cannot work reliably. The stall output signal become enabled when exceeding this velocity. It becomes disabled again once the velocity falls below this threshold.
  driver.semin(5);  // [0... 15] If the StallGuard4 result falls below SEMIN*32, the motor current becomes increased to reduce motor load angle.
  driver.semax(5);  // [0... 15]  If the StallGuard4 result is equal to or above (SEMIN+SEMAX+1)*32, the motor current becomes decreased to save energy.
  driver.sedn(0b01);  // current down step speed 0-11%
  driver.SGTHRS(STALL_VALUE);
  driver.pwm_autoscale(true);     // Needed for stealthChop
}

bool shaft = false;

void loop() {
  // Run 3200 steps and switch direction in software
  for (uint16_t i = 3200; i>0; i--) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(300);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(300);
  }
  delay(2000);
  shaft = !shaft;
  driver.shaft(shaft);
}

void diagnose(){
  Serial.println("stalking!");
}
