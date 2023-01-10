// ################################################################################################
// The MIT License (MIT)
//
// Copyright © 2022 Zefan Sramek
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this
// software and associated documentation files (the “Software”), to deal in the Software
// without restriction, including without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
// FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

// ################################################################################################

// BD-001 Hachimaru Firmware
// Version 2.1
// Written by: Zefan Sramek
// June, 2022

// ################################################################################################

// The production version of the firmware uses the MIDI Library Version 5.0
// https://github.com/FortySevenEffects/arduino_midi_library
#include <MIDI.h>

#define MODE_OMNI_ALL 0
#define MODE_OMNI_SINGLE 3
#define MODE_CHAN_ALL 1
#define MODE_CHAN_SINGLE 2

// This defines the MIDI note that will trigger the Hachimaru when in MODE_OMNI_SINGLE or MODE_CHAN_SINGLE:
#define DRUM_NOTE 36 // From the General MIDI Standard

// Pin Definitions
#define trigger 2 // This pin connects to the trigger input of the analog circuit through Q7.
#define led 9 // This corresponds to the power indicator LED on the front panel (D2).
#define trigger_bit_0 8 // The following pins all correspond to the DIP switch for controlling MIDI settings (SW2)
#define trigger_bit_1 7
#define midi_bit_0 6
#define midi_bit_1 5
#define midi_bit_2 4
#define midi_bit_3 3


// Function Definitions
void handle_note_on(byte inChannel, byte inNote, byte inVelocity);
void handle_note_off(byte inChannel, byte inNote, byte inVelocity);
void send_trigger();
void pin_setup();
void read_trigger_settings();
void read_midi_channel();

// State Variables
byte mode = 0;
byte midi_channel = 16;

// Create and bind the MIDI interface to the hardware serial port - Digital Pins 0 & 1
MIDI_CREATE_INSTANCE(HardwareSerial, Serial, EXT_MIDI);

void setup()
{
  // Initialize pins
  pin_setup();

  // Read initial MIDI settings
  read_trigger_settings();
  read_midi_channel();

  // Initialize MIDI
  EXT_MIDI.begin(MIDI_CHANNEL_OMNI);
  EXT_MIDI.turnThruOff();
  EXT_MIDI.setHandleNoteOn(handle_note_on);
  EXT_MIDI.setHandleNoteOff(handle_note_off);
}

void loop()
{
  // Handle the MIDI
  EXT_MIDI.read();

  // Handle the settings
  read_trigger_settings();
  read_midi_channel();
}

void handle_note_on(byte inChannel, byte inNote, byte inVelocity)
{
  if (mode == MODE_OMNI_ALL)
  {
    send_trigger();
    digitalWrite(led, LOW);
  }
  else if (mode == MODE_CHAN_ALL)
  {
    if (inChannel == midi_channel)
    {
      send_trigger();
      digitalWrite(led, LOW);
    }
  }
  else if (mode == MODE_CHAN_SINGLE)
  {
    if (inChannel == midi_channel && inNote == DRUM_NOTE)
    {
      send_trigger();
      digitalWrite(led, LOW);
    }
  }
  else if (mode == MODE_OMNI_SINGLE)
  {
    if (inNote == DRUM_NOTE)
    {
      send_trigger();
      digitalWrite(led, LOW);
    }
  }
}

void handle_note_off(byte inChannel, byte inNote, byte inVelocity)
{
  digitalWrite(led, HIGH);
}

void send_trigger()
{
  digitalWrite(trigger, HIGH);
  delay(20); // This sets the trigger pulse width.
  digitalWrite(trigger, LOW);
}

void pin_setup()
{
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  pinMode(trigger_bit_0, INPUT_PULLUP);
  pinMode(trigger_bit_1, INPUT_PULLUP);
  pinMode(midi_bit_0, INPUT_PULLUP);
  pinMode(midi_bit_1, INPUT_PULLUP);
  pinMode(midi_bit_2, INPUT_PULLUP);
  pinMode(midi_bit_3, INPUT_PULLUP);

  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, LOW);
}

void read_trigger_settings()
{
  byte bit_0 = 1 - digitalRead(trigger_bit_0);
  byte bit_1 = 1 - digitalRead(trigger_bit_1);
  mode = bit_0 | (bit_1 << 1);
}

void read_midi_channel()
{
  if (mode == MODE_CHAN_ALL || mode == MODE_CHAN_SINGLE)
  {
    // The inputs are using the internal pullup, so when the switch is on, we'll read 0. So we invert.
    byte bit_0 = 1 - digitalRead(midi_bit_0);
    byte bit_1 = 1 - digitalRead(midi_bit_1);
    byte bit_2 = 1 - digitalRead(midi_bit_2);
    byte bit_3 = 1 - digitalRead(midi_bit_3);
    midi_channel = (bit_0 | (bit_1 << 1) | (bit_2 << 2) | (bit_3 << 3)) + 1;
  }
}
