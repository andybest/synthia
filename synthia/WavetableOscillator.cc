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

#include "WavetableOscillator.h"

#include <math.h>

using namespace std;

namespace Synthia {
    void WavetableOscillator::init(SynthContext *ctx) {
        _ctx = ctx;
        
        _baseFrequency = 440.0f;
        _accumulator = 0.0;
        _interpolationType = kWavetableInterpolationLinear;
    }
    
    void WavetableOscillator::doPrecalculation(bool isSingleCycle)
    {
        _baseFrequency = _ctx->sampleRate() * _invNumSamples;
        _invBaseFrequency = 1.0f / (float)_baseFrequency;
        if(isSingleCycle)
        {
            // Is single cycle, so we don't need to scale anything
            _freqScale = 1.0f;
        }else{
            // Scale so that unpitched sound is at middle C
            _freqScale = _baseFrequency * (1.0f / 261.625565f);
        }
        calculatePhaseStep();
    }
    
    void WavetableOscillator::loadWavetable(string filename, bool isSingleCycle)
    {
        if(!_soundFile)
        {
            //_soundFile = new SoundFile();
        }
        
        _soundFile->loadWav(filename);
        
        _numSamples = _soundFile->length();
        _invNumSamples = 1.0f / (float)_numSamples;
        
        // Just use the left channel for now
        _sampleArray = _soundFile->samples()[0];
        
        doPrecalculation(isSingleCycle);
    }
    
    void WavetableOscillator::loadWavetableFromArray(const float *wtArray, int len, bool isSingleCycle)
    {
        _sampleArray = wtArray;
        _numSamples = len;
        _invNumSamples = 1.0f / (float)_numSamples;
        doPrecalculation(isSingleCycle);
    }
    
    void WavetableOscillator::setFrequency(float freq)
    {
        _freq = freq;
        calculatePhaseStep();
    }
    
    void WavetableOscillator::setInterpolationType(WavetableInterpolationType interpType)
    {
        _interpolationType = interpType;
    }
    
    void WavetableOscillator::retrigger()
    {
        _accumulator = 0.0;
    }
    
    void WavetableOscillator::calculatePhaseStep()
    {
        _phaseStep = (_freq * _invBaseFrequency) * _freqScale;
    }
    
}
