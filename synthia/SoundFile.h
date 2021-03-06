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


#ifndef __SoundFile_H_
#define __SoundFile_H_

#include "SError.h"

#include <string>

using std::string;

namespace Synthia
{
    struct SoundFileException
    {
        std::string s;
        SoundFileException(std::string ss) : s(ss) {}
        //~SoundFileException() throw () {}
        const char* what() const throw() { return s.c_str(); }
    };

    class SoundFile
    {
    public:
        SoundFile();
        ~SoundFile();
        void loadWav(string path);
        inline float *samples() { return _samples; }
        inline int length() { return _length; }
        inline int channels() { return _channels; }
        inline int sampleRate() { return _sampleRate; }

        void loadSamples(float *samples, int numChannels, int numSamples, int sampleRate);

    private:
        float *_samples;
        int _length;
        int _channels;
        int _sampleRate;
        bool _buffersAllocated;

    };
}

#endif //__SoundFile_H_
