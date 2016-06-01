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


#include "SObject.h"
#include "SynthContext.h"

#ifndef __Lowpass_H_
#define __Lowpass_H_

namespace Synthia
{
    class Lowpass : public SObject
    {
    public:
        void init(SynthContext *ctx);
        float tick(int channel, float input);
        void setCutoff(float cutoff);
        void setResonance(float resonance);
        

    protected:
        SynthContext *_ctx;
        
    private:
        float _cutoff;
        float _resonance;
        
        float q, p, f;
        
        float t1, t2, t3, t4;
        float b0, b1, b2, b3, b4;
        
        float in1, in2, in3, in4;
        float out1, out2, out3, out4;
        
        void calcCoefficients();
    };
    
}


#endif //__Lowpass_H_
