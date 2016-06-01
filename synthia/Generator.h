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

#ifndef __Generator_H_
#define __Generator_H_

namespace Synthia
{
    class Generator : public SObject
    {
    public:
        virtual ~Generator() {}
        virtual void init(SynthContext *ctx) = 0;
        virtual float tick(int channel) = 0;
        
        void tick(int channel, float *buffer, int bufLen)
        {
            for(int i = 0; i < bufLen; i++)
            {
                buffer[i] = tick(channel);
            }
        }

    protected:
        SynthContext *_ctx;
    };
    
    
    class PitchedGenerator : public Generator
    {
    public:
        virtual ~PitchedGenerator() {}
        virtual void setFrequency(float freq) = 0;
    protected:
        float _frequency;
    };
}


#endif //__Generator_H_
