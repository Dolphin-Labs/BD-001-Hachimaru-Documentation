# Dolphin Labs BD-001 Hachimaru
This repository contains the public technical documentation for the Dolphin Labs _BD-001 Hachimaru_.

## Demonstration Material

## User Manual

## Firmware

#### Overview
The `Firmware` folder contains the source code for the firmware for the BD-001. 
The BD-001 firmware is built using the [Arduino environment](https://www.arduino.cc/).

#### Libraries
The BD-001 firmware uses the [Arduino Midi Library](https://github.com/FortySevenEffects/arduino_midi_library). The production firmware currently uses Version 5.0.
The MIDI Library uses the [MIT License](https://github.com/FortySevenEffects/arduino_midi_library/blob/master/LICENSE) and the code is the copyright of Francois Best.

#### Licensing
The BD-001 firmware is also released under the MIT License. The license text is as follows:

````
The MIT License (MIT)

Copyright © 2022 Zefan Sramek

Permission is hereby granted, free of charge, to any person obtaining a copy of this
software and associated documentation files (the “Software”), to deal in the Software
without restriction, including without limitation the rights to use, copy, modify,
merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
````

#### Updating the Firmware
The hardware uses an ATMEGA 168 or 328 and can be updated either using the ICSP header located on the PCB, or by removing the chip and placing it in an Arduino Uno. If you intend to update your firmware, please note that not all chips are compatible with the Arduino environment by default, and may require modifications to the board definition file, etc. Please note that we cannot assist you with this process, so please ensure you know what you are doing before making any modifications.

## Hardware
The `Hardware` folder contains the schemtic for the BD-001. This schematic is provided for service and repair purposes only. It is provided as-is without warranty of any kind. Do not distribute the schematic without prior written permission. Instead, please link to this documentation repository.

### Service Notes
Here we provide a basic overview of some of the sub-systems of the BD-001 to help with troubleshooting potential issues.

#### Test Points
The BD-001 Rev.3 PCB provides the following test points:

TP1: Audio Output
TP2: Trigger Signal (after analogue and digital triggers have been combined)
TP3: MIDI Trigger Signal (generated by the microcontroller and driving Q7)
TP4: MIDI In (after isolation by U3)
TP5: +12V Rail
TP6: +5V Rail
TP7: Ground
TP8: -12V Rail

#### Power System
The BD-001 has three power rails: +12V, +5V, and -12V in addition to GND. The ±12V rails are generated by a [Mornsun A1212S-2WR3](https://www.mornsun-power.com/html/pdf/A1212S-2WR3.html) DC-DC converter. The +5V rail is generated by an standard 7805 5V regulator, operating off the +12V rail. In the event that the 12V power system fails, and a A1212S-2WR3 part can no longer be sourced, it can be replaced by any solution that can generate stable ±12V rails. See the schematic or datasheet for the pin-out of the A1212S-2WR3.

The BD-001 Rev.3 PCB also features a connector for a [Eurorack style power connector](https://doepfer.de/a100_man/a100t_e.htm). This can be used to power the board externally in the event of a failure in the power system. However, this may cause the existing power regulators to overheat, and the longterm impact of this on the existing power system has not been studied, so it is not recommended for prolonged use without modifications to the circuit.

#### Trigger Input
The analogue trigger input allows to BD-001 to be triggered from a variety of external equipment generator positive voltage trigger signals, e.g., Eurorack modules or analogue drum machines such as the Roland TR-606 (20V 20ms). The drum voice will be triggered on the rising edge of a positive voltage pulse. This input is buffered through the op-amp `U6`. It has been tested with DC voltage up to 30V without damage, but the under ideal operating conditions, trigger pulses are expected to be short. In the event of a rogue input (high positive voltage, negative voltage, AC signal, etc.) damage will most likely be limited to `U6` and potentially `R2`.

#### Microcontroller
The BD-001 is compatible with the ATMEGA328 and other pin-compatible microcontrollers, such as the ATMEGA168A and ATMEGA168PV. It uses a 16MHz external crystal for the clock generation, so any pin-compatible chip that supports this clock generation method should be compatible. As described above, the microcontroller can be re-programmed via the ICSP header located on the PCB.










