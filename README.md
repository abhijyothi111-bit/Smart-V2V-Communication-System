# Smart Vehicle-to-Vehicle (V2V) Communication System

A low-cost Arduino-based Vehicle-to-Vehicle communication prototype for transmitting accident alerts between vehicles using an MPU6050 accelerometer, SW-420 vibration sensor, 433 MHz RF communication, and an I2C LCD.

## Project Overview

The prototype is designed to improve road safety by detecting a possible accident condition on one vehicle and wirelessly communicating the status and measured angle to another vehicle.

The project documentation describes a broader Smart V2V Communication System with accident alerts, blind-spot detection, and emergency HELP alerts. The source code included in this repository specifically implements the **accident-alert communication portion**.

## Implemented System

### Transmitter (Vehicle 1)

The transmitter uses:

- MPU6050 accelerometer
- SW-420 vibration sensor
- Arduino
- 433 MHz RF transmitter

The Arduino reads the MPU6050 acceleration values, calculates a roll angle from the Y and Z axes, and reads the vibration sensor.

An accident alert is generated when:

```text
Vibration = HIGH
AND
|Roll Angle| > 35°
```

The transmitter sends:

```text
A,<angle>
```

for an alert condition, or:

```text
N,<angle>
```

for a normal condition.

### Receiver (Vehicle 2)

The receiver uses:

- Arduino
- 433 MHz RF receiver
- 16x2 I2C LCD

The receiver parses the transmitted status and angle and displays:

```text
STATUS: ALERT
ANGLE: 45
```

or:

```text
STATUS: NORMAL
ANGLE: 10
```

## Communication Flow

```text
        VEHICLE 1
┌─────────────────────────┐
│ MPU6050                 │
│ SW-420 Vibration Sensor │
└────────────┬────────────┘
             │
             ▼
       Arduino TX
             │
             ▼
      433 MHz RF TX
             │
             │ Wireless Alert
             ▼
      433 MHz RF RX
             │
             ▼
       Arduino RX
             │
             ▼
        I2C LCD
             │
             ▼
     Status + Angle
        VEHICLE 2
```

## Hardware Components

- Arduino Uno/Nano
- MPU6050 accelerometer/gyroscope
- SW-420 vibration sensor
- 433 MHz RF transmitter
- 433 MHz RF receiver
- 16x2 I2C LCD
- Jumper wires
- Breadboard
- Power supply

## Source Code

### Transmitter

`transmitter/v2v_transmitter.ino`

The transmitter reads the sensors and sends the status and angle through the RF module.

### Receiver

`receiver/v2v_receiver.ino`

The receiver receives the RF message, parses the status/angle, and displays the information on the LCD.

## Libraries

Install the following Arduino libraries before compiling:

- `MPU6050`
- `RadioHead` (`RH_ASK`)
- `LiquidCrystal_I2C`

The Arduino `Wire` and `SPI` libraries are used by the project.

## Pin Information

### Transmitter

| Component | Arduino Connection |
|---|---|
| SW-420 digital output | D2 |
| MPU6050 | I2C (SDA/SCL) |
| 433 MHz RF transmitter | RadioHead default TX pin D12 |

### Receiver

| Component | Arduino Connection |
|---|---|
| 433 MHz RF receiver | D2 |
| I2C LCD | I2C (SDA/SCL) |

## How to Run

### Transmitter

1. Open `transmitter/v2v_transmitter.ino` in Arduino IDE.
2. Install the required libraries.
3. Connect the MPU6050, SW-420, and RF transmitter.
4. Select the correct Arduino board and COM port.
5. Upload the transmitter sketch.
6. Open Serial Monitor at 9600 baud.
7. Confirm the `TX READY` message.

### Receiver

1. Open `receiver/v2v_receiver.ino`.
2. Install the required libraries.
3. Connect the RF receiver and I2C LCD.
4. Select the correct Arduino board and COM port.
5. Upload the receiver sketch.
6. Power both transmitter and receiver.
7. Observe the received status and angle on the LCD.

## Demo

The `demo/` folder contains videos showing the working prototype, including normal operation and an alert condition.

## Applications

- Vehicle accident warning
- Real-time hazard communication
- Road safety prototypes
- Intelligent transportation systems
- Future connected-vehicle safety systems

## Current Scope and Limitations

This repository documents the accident-alert portion supported by the available source code.

The presentation also describes ultrasonic blind-spot detection and a manual emergency HELP alert. Source code for those two functions was not included in the provided implementation, so they are not represented as implemented features here.

The accident condition is based on a fixed vibration and angle threshold, so further testing and calibration would be required for a production safety system.

## Future Improvements

- Integrate ultrasonic blind-spot detection.
- Add the emergency HELP alert function.
- Add GPS-based vehicle location.
- Add more robust communication and message validation.
- Add improved accident classification.
- Explore AI-based hazard detection.

## Project Documentation

The accompanying presentation describes the Smart Vehicle-to-Vehicle Communication System, its objectives, hardware, communication workflow, applications, and future scope.

## Author

Abhilash
