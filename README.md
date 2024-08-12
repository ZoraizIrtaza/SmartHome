# SmartHome
Innova Nest is a smart home made using arduino Uno and ESP 8266.

# Smart Home Project

This project focuses on building a smart home system using an ESP8266, Arduino, and the Blynk app. The system integrates various sensors and actuators to enable remote monitoring and control of the home environment, ensuring convenience, energy efficiency, and safety.

## Features

- **Real-time Monitoring**: Monitor temperature, humidity, gas levels, and soil moisture remotely.
- **Automation**: Automatic lighting control based on ambient light levels.
- **Remote Control**: Control lights, fans, and a servo-operated valve using the Blynk app.
- **Safety**: Gas sensor alerts in case of smoke or harmful gases.
- **Flexibility**: Easily add more sensors and actuators for expanded functionality.

## Components Used

- ESP8266
- Arduino
- PIR Sensor
- DHT11 Sensor
- MQ-7 Gas Sensor
- Soil Moisture Sensor
- Servo Motor
- LEDs
- Blynk App

## System Architecture

The system consists of an ESP8266 microcontroller that communicates with an Arduino to control various sensors and actuators. The data from the sensors is sent to the Blynk app, which allows for real-time monitoring and control through a mobile interface.

## Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/your_username/smart-home-project.git
   cd smart-home-project
