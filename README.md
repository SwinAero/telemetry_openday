# Arduino recorder for Telemetry
Arduino-side sketch for the telemetry demonstration at open day 2019.

This sketch dumps information from the 6-axis gyroscope onto a MicroSD card at approximately 90 data points per second.

## Libraries Used
- Our fork of [mpu6050_tockn](https://github.com/SwinAero/MPU6050_tockn)
- Standard Arduino SD library

## Components this is implemented against
- Arduino Uno R3
- [Arduino Ethernet Shield Rev 1 (W5100)](https://www.arduino.cc/en/Main/ArduinoEthernetShieldV1)
- GY-521 Breakout (MPU6050)

## Wiring
### GY-521
Arduino Pin | GY-521 Pin
:--:        | :--:
SCL (A5) | SCL
SDA (A4) | SDA
5V | VCC
GND | GND
D6 | INT

### Ethernet Shield
*This uses Hardware SPI*

Arduino Pin | Ethernet Shield Pin
:--:        | :--:
D4 | SS (MicroSD adapter)
D11 | MOSI
D12 | MISO
D13 | SCK
*D10* | *SS (Ethernet)*
