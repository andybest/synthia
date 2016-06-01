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

#include "SineOscillator.h"
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

namespace Synthia
{
    void SineOscillator::init(SynthContext *ctx)
    {
        this->_ctx = ctx;
        this->setFrequency(440.0f);
    }
    
    void SineOscillator::setFrequency(float freq)
    {
        this->_frequency = freq;
        _tickStep = ((M_PI * 2 * this->_frequency) / _ctx->sampleRate());
    }
    
    float SineOscillator::tick(int channel)
    {
        float samp = sinf(_phase);
        
        _phase += _tickStep;
        
        if(_phase > M_PI * 2)
            _phase -= M_PI * 2;
        
        return samp;
    }
}
