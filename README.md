# NodeMCU (ESP8266) Battery Voltage Monitor

A simple battery voltage monitor built with a NodeMCU (ESP8266), a resistor voltage divider and a 16x2 I2C LCD. The measured voltage is shown on the LCD and printed on the Serial Monitor.

I tested it with a 9V battery and a potentiometer. The idea comes from a Battery Monitor build exercise, which I rebuilt with my own components and code.

## Demo
![Setup](images/setup.jpg)

## Components
- NodeMCU ESP8266 (ESP-12E) x 1
- 9V battery x 1
- 10k resistor x 1
- Potentiometer x 1
- 16x2 LCD with I2C module x 1
- Breadboard and jumper wires

## Connections

| LCD I2C module | NodeMCU |
|---|---|
| GND | GND |
| VCC | VIN (5V), or 3V3 if your module works on it |
| SDA | D2 |
| SCL | D1 |

Voltage divider: Battery (+) -> R_TOP (20k) -> A0 -> R_BOTTOM (10k) -> GND

Battery (-) and NodeMCU GND must be connected together.

## How it works
1. `analogRead(A0)` reads the divider output (0 to 1023).
2. The reading is converted to the voltage at the A0 pin.
3. The battery voltage is calculated as: `V_battery = V_A0 x (R_TOP + R_BOTTOM) / R_BOTTOM`
4. The result is shown on the LCD and the Serial Monitor every second.

## How to run
1. Install the `LiquidCrystal_I2C` library in Arduino IDE.
2. Select the board **NodeMCU 1.0 (ESP-12E Module)**.
3. Open `battery_monitor.ino` (Arduino IDE may ask to move it into a folder, click OK), then upload.
4. Open the Serial Monitor at 115200 baud.
5. If the LCD stays blank, change the I2C address `0x27` to `0x3F`.

## Calibration
Compare the LCD reading with a multimeter. If they differ, adjust `A0_MAX_VOLTAGE` and the resistor values in the code. NodeMCU boards have an onboard divider on A0, so the correct value depends on your board.

## Safety
Never connect a battery directly to the A0 pin. Always use the voltage divider and keep the A0 voltage within your board's limit.
