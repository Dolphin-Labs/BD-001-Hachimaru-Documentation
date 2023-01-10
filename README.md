# Dolphin Labs BD-001 Hachimaru
This repository contains the public technical documentation for the Dolphin Labs _BD-001 Hachimaru_.

## Demonstration Material

## User Manual

## Firmware

#### Overview
The <Firmware> folder contains the source code for the firmware for the BD-001. 
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
