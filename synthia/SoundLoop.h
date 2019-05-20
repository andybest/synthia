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

#include "Generator.h"
#include "SoundFile.h"

#ifndef __SoundLoop_H_
#define __SoundLoop_H_


namespace Synthia
{
    class SoundLoop : public Generator
    {
    public:
        ~SoundLoop() {
            if(_soundFile != nullptr)
                delete _soundFile;
        }
        void loadFile(string filePath);

        void init(SynthContext *ctx);

        float tick(int channel);

        Frames &tick(Frames &frames);

        void loadSamples(float *samples, int numChannels, int numSamples)
        {
            if(_soundFile != nullptr)
                delete _soundFile;
            
            _soundFile = new SoundFile();
            _soundFile->loadSamples(samples, numChannels, numSamples, (int) _ctx->sampleRate());
            
            //if(_sampIdx != nullptr)
                delete [] _sampIdx;
            _sampIdx = new int[_soundFile->channels()];
        }
        
        bool isPlaying() {
            return _playing;
        }
        
        void setPlaying(bool playing) {
            _playing = playing;
            
            // Reset the sample to the beginning
            for(int i = 0; i < _soundFile->channels(); i++)
            {
                _sampIdx[i] = 0;
            }
        }
        
        void setLoops(bool loops) {
            _shouldLoop = loops;
        }

    private:
        SoundFile *_soundFile;
        int       *_sampIdx;
        bool      _playing;
        bool      _shouldLoop;
    };
}

#endif //__SoundLoop_H_
