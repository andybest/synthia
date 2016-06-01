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

#pragma once

#include <stdio.h>
#include "Synthia.h"
#include "SynthiaUtils.h"


namespace Synthia
{
    enum
    {
        kMoogVoiceParameter_OSC1_Waveform,
        kMoogVoiceParameter_OSC1_Volume,
        kMoogVoiceParameter_OSC1_Tune,
        kMoogVoiceParameter_OSC1_FineTune,
        
        kMoogVoiceParameter_OSC2_Waveform,
        kMoogVoiceParameter_OSC2_Volume,
        kMoogVoiceParameter_OSC2_Tune,
        kMoogVoiceParameter_OSC2_FineTune,
        
        kMoogVoiceParameter_OSC3_Waveform,
        kMoogVoiceParameter_OSC3_Volume,
        kMoogVoiceParameter_OSC3_Tune,
        kMoogVoiceParameter_OSC3_FineTune,
        
        kMoogVoiceParameter_Envelope_Attack,
        kMoogVoiceParameter_Envelope_Decay,
        kMoogVoiceParameter_Envelope_Sustain,
        kMoogVoiceParameter_Envelope_Release,
    };
    
    class MoogVoice : public SynthVoice
    {
    public:
        void init(SynthContext *ctx);
        
        void calcFrequencies(float baseFreq);
        void setFrequency(float freq);
        
        void keyOn();
        void keyOff();
        
        void changeValueForControlId(ControlEntryId id, float value);
        void processPitchBend(int pitchBendValue);
        void setupControlEntries();
        
        inline float tick(int channel)
        {
            float oscSamp = (_osc1.tick(channel) * _osc1Volume) + (_osc2.tick(channel) * _osc2Volume) + (_osc3.tick(channel) * _osc3Volume);
            float envelopeSamp = oscSamp * _envelope.tick(channel);
        
            return envelopeSamp;
        }
        
    private:
        SwitchableWavetableOscillator _osc1;
        SwitchableWavetableOscillator _osc2;
        SwitchableWavetableOscillator _osc3;
        
        //PulseOscillator _osc1;
        //PulseOscillator _osc2;
        //PulseOscillator _osc3;
        
        float _osc1Volume;
        float _osc1Tune;
        float _osc1FineTune;
        
        float _osc2Volume;
        float _osc2Tune;
        float _osc2FineTune;
        
        float _osc3Volume;
        float _osc3Tune;
        float _osc3FineTune;
        
        int _pitchBend;
        
        Envelope _envelope;
        
    };
}
