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

#include "Delay.h"
#include <stdio.h>

namespace Synthia {

    void Delay::init(SynthContext *ctx)
    {
        _ctx = ctx;
        setDelayTime(0.3);
        _delayIdx = 0;
        _feedback = 0.8;
        _volume = 0.0;
        
        _delaySamples = NULL;
        _delaySamples = (float *)malloc(sizeof(float) * SYNTHIA_DELAY_LENGTH);
        if(_delaySamples == NULL) {
            printf("Failed to allocate memory for delay!!!");
            return;
        }
        
        for(int i=0; i < SYNTHIA_DELAY_LENGTH; i++)
        {
            _delaySamples[i] = 0.0f;
        }
    }
    
    void Delay::setDelayTime(float delayTime)
    {
        _delayTime = delayTime;
        _delayLen = (unsigned int)(_delayTime * SYNTHIA_DELAY_LENGTH);
    }
    
    void Delay::setFeedbackLevel(float feedbackLevel)
    {
        _feedback = feedbackLevel;
    }
    
    void Delay::setDelayVolume(float delayVolume)
    {
        _volume = delayVolume;
    }
    
}