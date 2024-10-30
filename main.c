#include "driver.h"


// input pins
#define ArmButtonPin 13      // PC13
#define DisarmButtonPin 4    // PA4
#define FrontSensorPin 6     // PA6
#define BackSensorPin 7      // PA7
#define WindowSensorPin 9    // PA9

// output pins
#define ArmStatusPin 5       // PA5
#define FrontAlarmPin 0      // PB0
#define BackAlarmPin 5      // PB5
#define WindowAlarmPin 10    // PA10

int main(void) {
  // Turn on GPIO clocks (Ports A, B, and C)
  GPIOA_enable_clock();
  GPIOB_enable_clock();
  GPIOC_enable_clock();

  // Configure button pin as inputs
  GPIO_configure_input_mode(GPIOC, ArmButtonPin);      // configure ArmButtonPin as input
  GPIO_configure_input_mode(GPIOA, DisarmButtonPin);   // configure DisarmButtonPin as input

  // Configure reed switch pins as inputs
  GPIO_configure_input_mode(GPIOA, FrontSensorPin);    // configure FrontSensorPin as input
  GPIO_configure_input_mode(GPIOA, BackSensorPin);     // configure BackSensorPin as input
  GPIO_configure_input_mode(GPIOA, WindowSensorPin);   // configure WindowSensorPin as input

  // Enable pull resistors
  GPIO_enable_pull_up_resistor(GPIOA, DisarmButtonPin);    // enable pull-up resistor for DisarmButtonPin
  GPIO_enable_pull_up_resistor(GPIOA, FrontSensorPin);     // enable pull-up resistor for FrontSensorPin
  GPIO_enable_pull_up_resistor(GPIOA, BackSensorPin);      // enable pull-up resistor for BackSensorPin
  GPIO_enable_pull_up_resistor(GPIOA, WindowSensorPin);    // enable pull-up resistor for WindowSensorPin

  // Configure LED pins as outputs
  GPIO_configure_output_mode(GPIOA, ArmStatusPin);       // configure ArmStatusPin as output
  GPIO_configure_output_mode(GPIOB, FrontAlarmPin);      // configure FrontAlarmPin as output
  GPIO_configure_output_mode(GPIOB, BackAlarmPin);       // configure BackAlarmPin as output
  GPIO_configure_output_mode(GPIOA, WindowAlarmPin);     // configure WindowAlarmPin as output

  // Initialize Alarm Status (turn off all LEDs)
  GPIO_write_pin(GPIOA, ArmStatusPin, 0);    // turn off ArmStatus LED
  GPIO_write_pin(GPIOB, FrontAlarmPin, 0);   // turn off FrontAlarm LED
  GPIO_write_pin(GPIOB, BackAlarmPin, 0);    // turn off BackAlarm LED
  GPIO_write_pin(GPIOA, WindowAlarmPin, 0);  // turn off WindowAlarm LED

  // armed state (initialize to disarm)
  int armed = 0;	// not armed

  // infinite loop
  while (1) {
    // Part 5. Typed by Kein Lika.
    // check if ArmButton is pressed
    if (GPIO_read_pin(GPIOC, ArmButtonPin) == 0) {
      // arm system
      armed = 1;                                // set arm state
      GPIO_write_pin(GPIOA, ArmStatusPin, 1);   // turn on ArmStatus LED
    }

    // check if DisarmButton is pressed
    if (GPIO_read_pin(GPIOA, DisarmButtonPin) == 0) {
      // disarm system
      armed = 0;                                // reset arm state
      GPIO_write_pin(GPIOA, ArmStatusPin, 0);   // turn off ArmStatus LED
      GPIO_write_pin(GPIOB, FrontAlarmPin, 0);  // turn off FrontAlarm LED
      GPIO_write_pin(GPIOB, BackAlarmPin, 0);   // turn off BackAlarm LED
      GPIO_write_pin(GPIOA, WindowAlarmPin, 0); // turn off WindowAlarm LED
    }

    // if system is armed, check sensors
    if (armed) {
      // check the FrontSensor
      if (GPIO_read_pin(GPIOA, FrontSensorPin) != 0) {
        // system armed & front door is open:
        GPIO_write_pin(GPIOB, FrontAlarmPin, 1);  // turn on FrontAlarm LED
      }

      // check the BackSensor
      if (GPIO_read_pin(GPIOA, BackSensorPin) != 0) {
        // system armed & back door is open:
        GPIO_write_pin(GPIOB, BackAlarmPin, 1);   // turn on BackAlarm LED
      }

      // check the WindowSensor
      if (GPIO_read_pin(GPIOA, WindowSensorPin) != 0) {
        // system armed & window is open:
        GPIO_write_pin(GPIOA, WindowAlarmPin, 1); // turn on WindowAlarm LED
      }
    }
  }
}
