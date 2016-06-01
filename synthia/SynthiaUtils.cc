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

#include "SynthiaUtils.h"
#include <math.h>

namespace Synthia
{
    
    float SynthiaUtils::midiNoteToHz(unsigned int midiNote)
    {
        return 440.0f * powf( 2.0f, (midiNote - 69.0f) / 12.0f );
    }
    
    float SynthiaUtils::tuneFrequencyByCents(float frequency, float cents)
    {
        return frequency * powf(2, cents/1200.0f);
    }
    
    float SynthiaUtils::tuneFrequencyBySteps(float frequency, float steps)
    {
        return frequency * powf(2, steps/12.0f);
    }

}