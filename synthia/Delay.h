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

#include "Effect.h"
#include <stdlib.h>

#define SYNTHIA_DELAY_LENGTH 22050

namespace Synthia
{
    class Delay : public Effect
    {
    public:
        ~Delay() {};

        void init(SynthContext *ctx);
        
        void setDelayTime(float delayTime);
        void setFeedbackLevel(float feedbackLevel);
        void setDelayVolume(float delayVolume);
        
        inline float tick(int channel, float input)
        {   
            float delaySamp = _delaySamples[_delayIdx];
            float samp = (delaySamp * _volume) + input;
            _delaySamples[_delayIdx] = (input + delaySamp) * _feedback;
            
            // Wrap around buffer.
            if(++_delayIdx >= _delayLen)
                _delayIdx = 0;
            
            return samp;
        }
        
    private:
        float *_delaySamples;
        float _delayTime;
        unsigned int _delayLen;
        float _feedback;
        float _volume;
        unsigned int _delayIdx;
    };
}
