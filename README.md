# IoT-Enabled Worker Safety Monitoring Helmet

## Overview
An ESP32-based prototype that monitors gas levels, temperature, and vibration/impact
in real time to alert workers in hazardous environments such as mines and industrial
sites. Built and simulated in Wokwi due to lack of access to physical hardware.

## Problem
Workers in mining and industrial settings face risks from toxic gas exposure, heat
stress, and physical impacts that often go undetected until it's too late. This
project explores a low-cost, helmet-mounted sensor system that detects unsafe
conditions and raises alerts before they become dangerous.

## How It Works
- An **MQ-2 gas sensor** continuously monitors ambient gas concentration.
- A **DHT22 sensor** tracks temperature to flag heat-stress risk.
- A **potentiometer simulates a vibration/impact sensor** (used as a stand-in since
  Wokwi doesn't provide a dedicated vibration sensor component).
- The ESP32 reads all three sensors every 0.5 seconds and checks each against a
  safety threshold.
- Gas and vibration alerts use a **3-reading confirmation window** before firing, to
  filter out momentary sensor noise and avoid false alarms — a basic but real form
  of data validation.
- Every alert is timestamped, so response time can be measured directly from the
  serial output.

## Thresholds
- **Gas:** tuned to the simulator's sensor range (see code comments for reasoning)
- **Temperature:** 40°C, based on general heat-stress guidance for sustained industrial exposure
- **Vibration:** tuned to the simulator's potentiometer range as a stand-in signal

## Limitations (Simulation-Specific)
This was built entirely in Wokwi due to no access to physical components. As a result:
- Vibration is represented by a potentiometer, not a real accelerometer/vibration sensor
- Threshold values were tuned to the simulator's default sensor ranges rather than
  real-world MQ-2/accelerometer calibration data
- With real hardware, the next step would be calibrating thresholds against actual
  datasheet values and field testing

## What I'd Improve With Real Hardware
- Replace the potentiometer with an actual vibration/accelerometer sensor (e.g. SW-420 or MPU6050)
- Add buzzer/LED or app-based alerting instead of serial-only output
- Log historical data instead of just live readings
- Calibrate gas thresholds against real MQ-2 datasheet ppm values

## Tech Stack
ESP32, Embedded C (Arduino framework), PlatformIO, Wokwi Simulator
