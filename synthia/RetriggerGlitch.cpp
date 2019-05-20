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

#include "RetriggerGlitch.h"

namespace Synthia
{
    void RetriggerGlitch::init(SynthContext *ctx)
    {
        _ctx = ctx;

        _globalLocation = 0;
        _triggerLocation = 0;

        _grainOffset = 0.0f;
        _grainLength = 0;

        _playSpeed = 0.0f;
    }

    void RetriggerGlitch::loadSamples(float *samples, int numChannels, int numSamples, int triggerDivisions)
    {
        if (_soundFile != nullptr)
            delete _soundFile;

        _soundFile = new SoundFile();
        _soundFile->loadSamples(samples, numChannels, numSamples, (int) _ctx->sampleRate());

        _grainLength = (unsigned int) (numSamples / triggerDivisions);
        _retriggerSampleSize = _grainLength;
    }

    float RetriggerGlitch::tick(int channel)
    {
        return 0.0f;
    }

    Frames &RetriggerGlitch::tick(Frames &frames)
    {
        if (_soundFile == nullptr)
        {
            return frames;
        }

        for (unsigned int i = 0; i < frames.numSamples(); i++)
        {
            if (_globalLocation % _retriggerSampleSize == 0)
            {
                _triggerLocation = _globalLocation;
                _grainOffset = 0.0f;
            }

            int sampIdx = _triggerLocation + (int) _grainOffset;

            for (unsigned int channel = 0; channel < frames.numChannels(); channel++)
            {
                unsigned int idx  = (sampIdx * frames.numChannels()) + channel;
                float        samp = _soundFile->samples()[idx];
                frames[(i * frames.numChannels()) + channel] = samp;
            }

            // Increase global location counter to keep track of absolute timing
            _globalLocation += 1;

            if (_globalLocation >= _soundFile->length())
            {
                _globalLocation = 0;
            }

            // Increase grain offset
            _grainOffset += _playSpeed;

            if (_grainOffset >= _grainLength)
            {
                _grainOffset = fmodf(_grainOffset, _grainLength);
            }
        }

        return frames;
    }
}