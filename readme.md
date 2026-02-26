\# STM32 Multi-Sensor Data Hub





\##  Project Overview

This project uses an STM32 Blue Pill to read data from three sensors:

&nbsp;1) DHT11 – Temperature and humidity

&nbsp;2) HC-SR50 – PIR motion sensor

&nbsp;3) SW-520D – Tilt switch



Data is transmitted via UART to a PC for real‑time monitoring which is ideal for weather stations, security systems, or learning embedded systems.



\## Hardware Required

&nbsp; Component used

&nbsp; STM32 Blue Pill (STM32F103C8)

&nbsp; DHT11 sensor

&nbsp; HC-SR501 PIR sensor

&nbsp; SW-520D tilt switch

&nbsp; 4.7kΩ resistor (DHT11 pull-up)

&nbsp; 4.7kΩ resistor (tilt pull-up)

&nbsp; USB‑to‑TTL adapter (FTDI/CH340) 

&nbsp; ST‑Link programmer

&nbsp; Breadboard, jumper wires 

&nbsp; 



\## Wiring Diagram

&nbsp;Open docs folder and see the wiring diagram.



&nbsp; STM32 Pin Connection



&nbsp; 3.3V supplied DHT11 VCC, tilt pull-up 

&nbsp; 5V supplied HC-SR501 VCC 

&nbsp; GND connected to DHT11 GND, HC-SR501 GND, tilt switch one leg 

&nbsp; PB0 connected to DHT11 DATA (with 4.7kΩ pull-up) 

&nbsp; PB1 connected HC-SR501 OUT 

&nbsp; PA7 connected Tilt switch other leg (with 4.7kΩ pull-up) 

&nbsp; PA9 connected USART1 TX (to FTDI RX) 

&nbsp; PA10 connected to USART1 RX (to FTDI TX) 



\## Software Setup

1\. Clone this repository.

2\. Open the `.ioc` file with STM32CubeMX and regenerate code.

3\. Open the Keil project, build and flash.

4\. Connect FTDI, open serial monitor at 115200 baud, press RESET.



\## Data Format

Example: `5000,Temp:24.5,Hum:60.0,motion:1,tilt:0`



\## Demo Video

[https://drive.google.com/file/d/1DYNC\_YmzdhdJdVzSkgDfIx1iOHbnZrZt/view?usp=drive\_link](https://drive.google.com/file/d/1DYNC_YmzdhdJdVzSkgDfIx1iOHbnZrZt/view?usp=drive_link)

