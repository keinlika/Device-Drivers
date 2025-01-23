# Device Drivers - Home Security System Using STM32 Microcontroller 

## Project Overview
This project is a simple home security system implemented on an STM32 microcontroller. It utilizes device drivers to manage GPIO pins for input and output, enabling sensors to detect unauthorized entry and LEDs to signal alarms. The system can be armed and disarmed using buttons, with specific alarms triggered by various entry points (doors, windows).

## Hardware Schematic
<img width="511" alt="image" src="https://github.com/user-attachments/assets/04c842ef-e91a-44e4-9db2-6d7571eed0d2">

*Figure 1: Schematic showing the connections for the final circuit.*

## Specifications
- **GPIO Clocks**: Enable clocks for GPIO ports A, B, and C using the following functions:
  - `GPIOA_enable_clock()`
  - `GPIOB_enable_clock()`
  - `GPIOC_enable_clock()`

- **GPIO Configuration**:
  - **Input Mode**: Pins configured as input are for buttons and sensors.
    - `ArmButtonPin (PC13)`, `DisarmButtonPin (PA4)`, `FrontSensorPin (PA6)`, `BackSensorPin (PA7)`, `WindowSensorPin (PA9)`
  - **Output Mode**: Pins configured as output control status and alarm LEDs.
    - `ArmStatusPin (PA5)`, `FrontAlarmPin (PB0)`, `BackAlarmPin (PB5)`, `WindowAlarmPin (PA10)`

- **GPIO Pull-Up Resistors**:
  - Enabled for `DisarmButtonPin`, `FrontSensorPin`, `BackSensorPin`, and `WindowSensorPin` to ensure stable input readings.

## Functions
- **GPIO Configuration Functions**:
  - `GPIO_configure_input_mode(Port* GPIOx, unsigned int pin)`
  - `GPIO_configure_output_mode(Port* GPIOx, unsigned int pin)`
  - `GPIO_enable_pull_up_resistor(Port* GPIOx, unsigned int pin)`
  - `GPIO_read_pin(Port* GPIOx, unsigned int pin)`
  - `GPIO_write_pin(Port* GPIOx, unsigned int pin, unsigned int state)`

## Test Plan and Results
| Test Scenario            | Expected Result                        | Observed Result                     |
|--------------------------|----------------------------------------|-------------------------------------|
| Button 1 pressed         | System Armed (LED 1 on)               | System Armed (LED 1 on)            |
| Button 2 pressed         | System Disarmed (LED 1 off)           | System Disarmed (LED 1 off)        |
| Front door opens         | Triggers alarm, Green LED turns on    | Green LED turns on                 |
| Back door opens          | Triggers alarm, Yellow LED turns on   | Yellow LED turns on                |
| Window opens             | Triggers alarm, Blue LED turns on     | Blue LED turns on                  |

*Table 1: Test plan with expected and observed results.*

## Evidence of Correct Operation
[Link to Video Demonstration](https://vimeo.com/1024617014?share=copy)

## Code Files
- `main.c`: Contains the main program for the security system.
- `driver.h`: Header file defining GPIO configuration functions.
