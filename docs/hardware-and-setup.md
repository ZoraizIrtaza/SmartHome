# Hardware and Setup

## Main Components

| Component | Interface | Role |
|---|---|---|
| ESP8266 | Wi-Fi / GPIO / ADC / Serial | IoT gateway |
| DHT11 | Digital | Temperature and humidity |
| PIR sensor | Digital | Motion detection |
| LDR | Analog | Ambient-light measurement |
| MQ-7 | Serial value from companion controller | Gas/smoke measurement |
| LED / light | Digital output | Automatic lighting |
| Arduino / companion controller | Serial | Provides the MQ-7 reading |

## ESP8266 Pin Configuration

The maintained firmware uses:

```cpp
DHT_PIN = 2
PIR_PIN = 5
LED_PIN = D2
LDR_PIN = A0
```

If the physical prototype uses different pins, update these constants before uploading.

## Serial Gas-Sensor Input

The ESP8266 expects one MQ-7 reading per line.

Example:

```text
245
263
318
```

Each line should contain an integer followed by `\n`.

The latest valid reading is:

- sent to Blynk virtual pin `V1`;
- compared with the gas alert threshold;
- used to generate the `smoke_detected` event when the threshold is crossed.

## Blynk Setup

Create the following datastreams in the Blynk template:

| Virtual Pin | Suggested Type |
|---|---|
| V1 | Integer |
| V5 | Double |
| V6 | Double |
| V7 | Integer |
| V8 | Integer |

Create these events:

```text
motion_detected
smoke_detected
```

Add suitable dashboard widgets for the sensor values in the Blynk mobile or web interface.

## Thresholds

The firmware keeps the main tuning values near the top of the sketch:

```cpp
LIGHT_THRESHOLD = 500
GAS_ALERT_THRESHOLD = 300
TEMPERATURE_OFFSET_C = 3.0
SENSOR_INTERVAL_MS = 1000
```

These values came from the prototype configuration and may require recalibration for different sensors or wiring.

## Important Hardware Note

Gas sensors and ESP8266 analog inputs have voltage and current requirements that depend on the exact modules being used. The sensor output must remain within the safe input range of the board/interface being connected.

The prototype should not be treated as a certified smoke, carbon-monoxide, fire or security alarm.
