/*

MIT License

Copyright (c) 2017 Andy Best

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

#pragma mark

#include "Synthia.h"
#include "Frames.h"

namespace Synthia
{
    class RetriggerGlitch : Generator
    {
    public:
        void init(SynthContext *ctx);

        void loadSamples(float *samples, int numChannels, int numSamples, int triggerDivisions);

        Frames &tick(Frames &frames);

        float tick(int channel);

        void setPlaySpeed(float playSpeed) {
            _playSpeed = playSpeed;
        }

        void setGrainLength(float grainLength) {
            _grainLengthRatio = grainLength;

            _grainLength = (unsigned int)(_retriggerSampleSize * _grainLengthRatio);
        }

    private:
        /*
         * Used for timekeeping. Will keep position in the sample as if it is a loop.
         */
        unsigned int _globalLocation;


        /*
         * The current location of the granular window in the sample
         */
        unsigned int _triggerLocation;

        /*
         * The offset within the grain
         */
        float _grainOffset;
        float _grainLengthRatio;
        unsigned int _grainLength;

        float _playSpeed;

        /*
         * The number of samples between each retrigger zone
         * e.g. for a 4 bar loop of 1000000 samples retriggering on each beat,
         * this would be set to 250000
         */
        int _retriggerSampleSize;

        SoundFile *_soundFile;
    };
}