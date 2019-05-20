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

#include <cstdlib>
#include <algorithm>
#include "Frames.h"

namespace Synthia
{
    Frames::Frames(unsigned int numSamples, unsigned int numChannels)
    {
        _numSamples  = numSamples;
        _numChannels = numChannels;

        _samples = new float[_numSamples * _numChannels];

        for(unsigned int i = 0; i < _numSamples * _numChannels; i++) {
            _samples[i] = 0;
        }
    }

    Frames::~Frames()
    {
        if (_samples != nullptr)
        {
            delete[] _samples;
        }
    }

    Frames::Frames(const Frames &framesToCopy)
    {
        // Copy constructor

        _numSamples  = framesToCopy._numSamples;
        _numChannels = framesToCopy._numChannels;
        _samples     = new float[_numSamples * _numChannels];

        std::copy(framesToCopy._samples, framesToCopy._samples + (_numSamples * _numChannels), _samples);
    }

    Frames &Frames::operator=(const Frames &frames)
    {
        if (_numSamples != frames._numSamples || _numChannels != frames._numChannels)
        {
            _numSamples  = frames._numSamples;
            _numChannels = frames._numChannels;

            if (_samples != nullptr)
            {
                delete[] _samples;
            }

            _samples = new float[_numSamples * _numChannels];
        }

        std::copy(frames._samples, frames._samples + (_numSamples * _numChannels), _samples);

        return *this;
    }


}
