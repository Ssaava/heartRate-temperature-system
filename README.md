# Health Monitoring Sub-system

## Keeping up with your Health

## Table of contents

# Table of Contents

- [Brief Description](#brief-description)
- [Components to be Used](#components-to-be-used)
  - [Heartbeat Sensor](#heartbeat-sensor)
  - [SIM Module](#sim-module)
  - [DHT Sensor](#dht-sensor)
  - [Arduino](#arduino)
  - [Buzzer](#buzzer)
  - [Light Emitting Diode(LED)](#light-emitting-dioodeled)
  - [Liquid Crystal Display](#liquid-crystal-display)
- [Libraries Used](#libraries-used)
  - [SPI](#spi)
  - [Wire](#wire)
  - [Adafruit_GFX](#adafruit_gfx)
  - [Adafruit_SSD1306](#adafruit_ssd1306)
  - [dht](#dht)
  - [PulseSensorPlayground](#pulsesensorplayground)
  - [SoftwareSerial](#softwareserial)
  - [String](#string)

---

## Brief Description

The health monitoring system collects real time data of the patient’s heart rate using the and body temperature and the real time data transferred to Thing Speak for storage periodically.
These values are retrieved from the things speak which are then displayed to the patient accompanied with the state condition of the their heart rate( Low, normal, High). Once the heart rate or body temperature changes to a certain threshold the that needs attention, the led lights and the buzzer are used to notify an emergency.

---

## Components to be Used

- Heartbeat Sensor
- SIM Module
- DHT Sensor
- Arduino
- Liquid Crystal Display (LCD)
- Buzzer
- Light Emitting Diodes (LED)

## Heartbeat Sensor

Also known as a pulse sensor, it is used to measure the heart rate of an individual by detecting changes in blood volume in the microvascular tissue. Typically, it consists of an infrared LED and a photodetector placed on a fingertip or earlobe. When the heart beats, blood flow increases, causing a detectable change in the amount of light absorbed by the photodetector.

## SIM Module

A SIM (Subscriber Identity Module) This SIM module is to be used in for adding cellular connectivity to devices. To allow device to send and receive data over cellular networks, enabling features such as remote monitoring, control, and communication.

## DHT Sensor

A DHT sensor is to be used for capturing the temperature of the body.
This can be placed in certain body parts like the armpits or a closed hand palm to capture real time data without disturbances from the environment

## Arduino

Arduino is an open-source electronics platform based on easy-to-use hardware and software. It consists of a microcontroller board (e.g., Arduino Uno, Arduino Mega) and a development environment for writing, compiling, and uploading code to the board. Arduino boards are widely used in embedded systems projects due to their simplicity, versatility, and large community support.

## Buzzer

The buzzer which is a sound emitting device will produce sound for a specified period of time if there is a detection of changes in either the temperature or the heart rate values to critical values

## Light Emitting Diode(LED)

The LED will emit light to signify need for an action in case there is a detection of changes in either the temperature or the heart rate values to critical values.

## Liquid Crystal Display

The LCD will print the real time changing values of the heart rate and temperature on its screen for easy monitoring and measurements reviews.

---

## Libraries Used

- SPI
- Wire
- Adafruit_GFX
- Adafruit_SSD1306
- dht
- PulseSensorPlayground
- SoftwareSerial
- String

# SPI

SPI stands for Serial Peripheral Interface. It's a synchronous serial communication interface used for short-distance communication, primarily in embedded systems.

## Wire

Wire is a library for I2C communication, allowing Arduino to communicate with other devices via the I2C protocol.

## Adafruit_GFX

Adafruit_GFX is a graphics library providing a common set of graphics primitives (points, lines, circles, etc.) that work across different displays.

## Adafruit_SSD1306

Adafruit_SSD1306 is a library for controlling OLED displays based on the SSD1306 driver chip. It provides functions for drawing text, shapes, and images on OLED screens.

## dht:\*\*

The dht library is used for interfacing with DHT series temperature and humidity sensors. It provides functions to read temperature and humidity data from the sensor.

## PulseSensorPlayground

PulseSensorPlayground is a library for interfacing with pulse sensors. It simplifies reading heartbeat data from pulse sensors and provides utilities for processing the signal.

## SoftwareSerial

SoftwareSerial is a library that allows serial communication on digital pins other than the hardware serial pins (0 and 1). It's useful for communication with devices like SIM modules that require serial communication.

## String

The String library provides functions and utilities for working with strings of characters in Arduino sketches. It simplifies string manipulation tasks.
