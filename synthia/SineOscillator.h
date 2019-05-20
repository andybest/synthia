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

#include <cmath>
#include "Generator.h"

namespace Synthia
{

    class SineOscillator : public PitchedGenerator
    {
    public:
        void init(SynthContext *ctx);

        void setFrequency(float freq);

        float tick(int channel);

        inline virtual Frames &tick(Frames &frames)
        {
            for (unsigned int i = 0; i < frames.numSamples(); i++)
            {
                float samp = sinf(_phase);

                _phase += _tickStep;

                if (_phase > M_PI * 2)
                    _phase -= M_PI * 2;

                for (unsigned int channel = 0; channel < frames.numChannels(); channel++)
                {
                    frames[(i * frames.numChannels()) + channel] = samp;
                }
            }

            return frames;
        }

    private:
        float _phase;
        float _tickStep;
        float _lastSamp;
    };
}