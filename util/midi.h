/*

MIT License
 
Copyright (c) 2016 Andy Best

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef MIDI_H
#define	MIDI_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MIDI_GET_MESSAGE_TYPE(x)        x & 0xF0
#define MIDI_GET_MESSAGE_CHANNEL(x)     x & 0x0F
    
#define MIDI_MESSAGE_NOTE_OFF           0x8
#define MIDI_MESSAGE_NOTE_ON            0x9
#define MIDI_MESSAGE_AFTERTOUCH         0xA
#define MIDI_MESSAGE_CONTROL_CHANGE     0xB
#define MIDI_MESSAGE_PROGRAM_CHANGE     0xC
#define MIDI_MESSAGE_CHANNEL_PRESSURE   0xD
#define MIDI_MESSAGE_PITCH_BEND         0xE
    
    typedef struct {
        uint8_t channel:4;
        uint8_t type:4;
        
        union {
            struct {
                uint8_t velocity: 7;
                uint8_t key: 7;
            }NoteOn;
            
            struct {
                uint8_t velocity: 7;
                uint8_t key: 7;
            }NoteOff;
            
            struct {
                uint8_t velocity: 7;
                uint8_t key: 7;
            }AfterTouch;
            
            struct {
                uint8_t controllerValue: 7;
                uint8_t controllerNumber: 7;
            }ControlChange;
            
            struct {
                uint8_t programNumber;
            }ProgramChange;
            
            struct {
                uint8_t velocity;
            }ChannelPressure;
            
            struct {
                int16_t pitchBendValue;
            }PitchBend;
        };
    }MidiMessage_t;

#ifdef	__cplusplus
}
#endif

#endif	/* MIDI_H */

