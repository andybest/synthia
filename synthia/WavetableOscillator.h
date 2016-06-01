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

#ifndef __Callisto__WavetableOscillator__
#define __Callisto__WavetableOscillator__

//#include <iostream>

#include "Generator.h"
#include "SoundFile.h"
#include <math.h>

namespace Synthia {
    
    typedef enum {
        kWavetableInterpolationNone,
        kWavetableInterpolationLinear
    } WavetableInterpolationType;
    
    class WavetableOscillator : public PitchedGenerator
    {
    public:
        void init(SynthContext *ctx);
        void setFrequency(float freq);
        void setInterpolationType(WavetableInterpolationType interpType);
        void doPrecalculation(bool isSingleCycle);
        void loadWavetable(string filename, bool isSingleCycle);
        void loadWavetableFromArray(const float *wtArray, int len, bool isSingleCycle);
        void retrigger();
        
        inline float tick(int channel)
        {
            float samp;
        
            if(_interpolationType == kWavetableInterpolationNone)
            {
                int sampleIdx = (int)_accumulator;
                samp = _sampleArray[sampleIdx];
            } else {
                // Interpolate between the 2 nearest samples to the accumulator
                int idxBase = (int)floor(_accumulator);
                float idxFrac = _accumulator - idxBase;
            
                // Get floor and ceil values
                float val = _sampleArray[idxBase];
                int idx2 = idxBase + 1;
                
                if(idx2 >= _numSamples)
                    idx2 = 0;
                float val2 = _sampleArray[idx2];
            
                samp = val + ((val2 - val) * idxFrac);
            }
       
            _accumulator += _phaseStep;
        
            if(_accumulator > _numSamples) {
                _accumulator -= _numSamples;
            }
            return samp;
        }
        
    private:
        void calculatePhaseStep();
        
        SoundFile *_soundFile;
        
        const float *_sampleArray;
        int _numSamples;
        float _invNumSamples;
        
        float _baseFrequency;
        float _invBaseFrequency;
        float _freq;
        float _freqScale;
        float _phaseStep;
        float _accumulator;
        WavetableInterpolationType _interpolationType;
    };
}

#endif /* defined(__Callisto__WavetableOscillator__) */
