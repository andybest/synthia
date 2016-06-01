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
#include <vector>

#include "SynthContext.h"
#include "Generator.h"
#include "WavetableOscillator.h"

namespace Synthia
{
    class SwitchableWavetableOscillator : public PitchedGenerator
    {
    public:
        void init(SynthContext *ctx);
        void setFrequency(float freq);
        
        int addWavetable(const float *sampleArray, int len);
        void selectWavetable(int wavetableIdx);
        void selectWavetableFloat(float value);
        
        unsigned int numWavetables();
        
        inline float tick(int channel)
        {
            /*if (channel >= _wavetableOscillators.size()) {
                return 0.0f;
            }*/
            
            return _currentOsc->tick(channel);
            //return _wavetableOscillators[_selectedOscillator]->tick(channel);
        }
        
    private:
        unsigned int _selectedOscillator;
        WavetableOscillator *_currentOsc;
        std::vector<WavetableOscillator *> _wavetableOscillators;
        
    };
}

