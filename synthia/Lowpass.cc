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

#include "Lowpass.h"
#include <math.h>
#include <stdio.h>

namespace Synthia
{   
    void Lowpass::init(SynthContext *ctx)
    {
        this->_ctx = ctx;
        in1 = in2 = in3 = in4 = 0.0f;
        out1 = out2 = out3 = out4 = 0.0f;
    }
    
    void Lowpass::setCutoff(float cutoff)
    {
        if (cutoff < 0) {
            cutoff = 0;
        }else if (cutoff > _ctx->sampleRate()) {
            cutoff = _ctx->sampleRate();
        }
        _cutoff = cutoff;
        //printf("Cutoff: %f\n", _cutoff);
        //calcCoefficients();
    }
    
    void Lowpass::setResonance(float resonance)
    {
        if(resonance < 0) {
            resonance = 0;
        } else if(resonance > 4) {
            resonance = 4;
        }
        printf("Resonance: %f\n", _resonance);
        _resonance = resonance;
        //calcCoefficients();
    }
    
    void Lowpass::calcCoefficients()
    {
        float frequency = _cutoff / (_ctx->sampleRate()/2.0f);
        q = 1.0f - frequency;
        p = frequency + 0.8f * frequency * q;
        f = p + p - 1.0f;
        q = _resonance * (1.0f + 0.5f * q * (1.0f - q + 5.6f * q * q));
    }
    
    float Lowpass::tick(int channel, float input)
    {
        float f = _cutoff * 1.16f;
        float fb = _resonance * (1.0f - 0.15f * f * f);
        input -= out4 * fb;
        input *= 0.35013 * (f*f)*(f*f);
        out1 = input + 0.3f * in1 + (1.f - f) * out1; // Pole 1
        in1 = input;
        out2 = out1 + 0.3f * in2 + (1.f - f) * out2; // Pole 2
        in2 = out1;
        out3 = out2 + 0.3f * in3 + (1.f - f) * out3; // Pole 3
        in3 = out2;
        out4 = out3 + 0.3f * in4 + (1.f - f) * out4; // Pole 4
        in4 = out3;
        return out4;
    }
}
