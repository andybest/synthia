#pragma once
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
#include <cassert>

namespace Synthia
{
    class Frames
    {

    public:
        Frames(unsigned int numSamples, unsigned int numChannels);

        ~Frames();

        Frames(const Frames &framesToCopy);

        // Operators
        Frames &operator=(const Frames &frames);

        float& operator[](size_t idx);

        float operator[](size_t idx) const;

        Frames operator+(const Frames &framesToAdd) const;

        void operator+=(const Frames &framesToAdd);

        Frames operator-(const Frames &framesToSubtract) const;

        void operator-=(const Frames &framesToSubtract);

        Frames operator*(const Frames &framesToMultiply) const;

        void operator*=(const Frames &framesToMultiply);

        Frames operator*(const float scalar) const;

        void operator*=(const float scalar);


        unsigned int numChannels()
        {
            return _numChannels;
        }

        unsigned int numSamples()
        {
            return _numSamples;
        }

    private:
        unsigned int _numChannels;
        unsigned int _numSamples;
        float        *_samples;
    };

    inline float& Frames::operator[](size_t idx)
    {
        assert(_samples != nullptr && idx < _numChannels * _numSamples);
        return _samples[idx];
    }

    inline float Frames::operator[](size_t idx) const
    {
        assert(_samples != nullptr && idx < _numChannels * _numSamples);
        return _samples[idx];
    }

    inline Frames Frames::operator+(const Frames &framesToAdd) const
    {
        Frames summed(_numSamples, _numChannels);

        float *dstPtr = summed._samples;
        float *rhsPtr = framesToAdd._samples;
        float *lhsPtr = _samples;

        for (unsigned int i = 0; i < _numChannels * _numSamples; i++)
        {
            *dstPtr++ = *lhsPtr++ + *rhsPtr++;
        }

        return summed;
    }

    inline void Frames::operator+=(const Frames &framesToAdd)
    {
        float *srcPtr = framesToAdd._samples;
        float *dstPtr = _samples;

        for (unsigned int i = 0; i < _numChannels * _numSamples; i++)
        {
            *dstPtr++ += *srcPtr++;
        }
    }

    inline Frames Frames::operator-(const Frames &framesToSubtract) const
    {
        Frames subtracted(_numSamples, _numChannels);

        float *dstPtr = subtracted._samples;
        float *rhsPtr = framesToSubtract._samples;
        float *lhsPtr = _samples;

        for (unsigned int i = 0; i < _numChannels * _numSamples; i++)
        {
            *dstPtr++ = *lhsPtr++ - *rhsPtr++;
        }

        return subtracted;
    }

    inline void Frames::operator-=(const Frames &framesToSubtract)
    {
        float *srcPtr = framesToSubtract._samples;
        float *dstPtr = _samples;

        for (unsigned int i = 0; i < _numChannels * _numSamples; i++)
        {
            *dstPtr++ -= *srcPtr++;
        }
    }

    inline Frames Frames::operator*(const Frames &framesToMultiply) const
    {
        Frames multiplied(_numSamples, _numChannels);

        float *dstPtr = multiplied._samples;
        float *rhsPtr = framesToMultiply._samples;
        float *lhsPtr = _samples;

        for (unsigned int i = 0; i < _numChannels * _numSamples; i++)
        {
            *dstPtr++ = *lhsPtr++ * *rhsPtr++;
        }

        return multiplied;
    }

    inline void Frames::operator*=(const Frames &framesToMultiply)
    {
        float *srcPtr = framesToMultiply._samples;
        float *dstPtr = _samples;

        for (unsigned int i = 0; i < _numChannels * _numSamples; i++)
        {
            *dstPtr++ *= *srcPtr++;
        }
    }

    inline Frames Frames::operator*(const float scalar) const
    {
        Frames multiplied(_numSamples, _numChannels);

        float *dstPtr = multiplied._samples;
        float *lhsPtr = _samples;

        for (unsigned int i = 0; i < _numChannels * _numSamples; i++)
        {
            *dstPtr++ = *lhsPtr++ * scalar;
        }

        return multiplied;
    }

    inline void Frames::operator*=(const float scalar)
    {
        float *dstPtr = _samples;

        for (unsigned int i = 0; i < _numChannels * _numSamples; i++)
        {
            *dstPtr++ *= scalar;
        }
    }
}