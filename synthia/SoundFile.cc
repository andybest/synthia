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

#include "SoundFile.h"

#include <fstream>
#include <iostream>

#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"

//#include "SEndian.h"

#define EXTRACT_16(x) ((x[0] << 0) | (x[1]<< 8))
#define EXTRACT_32(x) ((x[0] << 0) | (x[1]<< 8) | (x[2] << 16) | (x[3] << 24))

using namespace std;

namespace Synthia
{
    SoundFile::SoundFile()
    {
        _buffersAllocated = false;
        _samples = nullptr;
    }

    SoundFile::~SoundFile()
    {
        // Deallocate sample buffers
        if(_buffersAllocated) {
            free(_samples);
        }
    }

    void SoundFile::loadSamples(float *samples, int numChannels, int numSamples, int sampleRate) {
        _samples = samples;
        
        //_samples = (float *)malloc(sizeof(float) * numSamples * numChannels);
        //_buffersAllocated = true;
        //memcpy(_samples, samples, sizeof(float) * numSamples * numChannels);

        _channels = numChannels;
        _length = numSamples;
        _sampleRate = sampleRate;
    }
    
    void SoundFile::loadWav(string path)
    {
//        ifstream wavFile;
//
//        try
//        {
//            wavFile.open(path, ios::in );
//        } catch(const ifstream::failure& e) {
//            throw SoundFileException("File not found");
//            return;
//        }
//
//        // Get length of file:
//        wavFile.seekg (0, wavFile.end);
//        int length = (int)wavFile.tellg();
//        wavFile.seekg (0, wavFile.beg);
//
//        if(length < 1)
//            throw SoundFileException("File has zero length");
//
//        // Put file into buffer
//        unsigned char *fileBuffer = new unsigned char [length];
//        wavFile.read((char *)fileBuffer, length);
//
//        wavFile.close();
//
//        cout << "File length: " << length << endl;
//
//        /* RIFF header */
//        char id[5];
//        unsigned int chunkSize;
//        char format[5];
//        id[4] = '\0';
//        format[4] = '\0';
//
//        unsigned char uint16Buf[2];
//        unsigned char uint32Buf[4];
//
//        memcpy(id, fileBuffer, sizeof(char) * 4);
//        memcpy(format, &fileBuffer[8], sizeof(char) * 4);
//
//        if(strcmp(id, "RIFF") || strcmp(format, "WAVE"))
//        {
//            delete[] fileBuffer;
//            throw SoundFileException("Invalid file format");
//        }
//
//        //
//        memcpy(uint32Buf, &fileBuffer[4], sizeof(char) * 4);
//        chunkSize = EXTRACT_32(uint32Buf);
//
//        /* fmt Chunk */
//
//        // Get the size of the format chunk
//        unsigned int subChunk1Size;
//        memcpy(uint32Buf, &fileBuffer[16], sizeof(char) * 4);
//        subChunk1Size = EXTRACT_32(uint32Buf);
//
//        // Get the format of the audio (PCM is 1)
//        unsigned int audioFormat;   // 16 bit value
//        memcpy(uint16Buf, &fileBuffer[20], sizeof(char) * 2);
//        audioFormat = EXTRACT_16(uint16Buf);
//
//        if(audioFormat != 1 && audioFormat != 0xFFFE)
//        {
//            delete[] fileBuffer;
//            throw SoundFileException("This decoder only supports PCM encoded WAV files.");
//        }
//
//        // Get number of channels
//        unsigned int numChannels;   // 16 bit value
//        memcpy(uint16Buf, &fileBuffer[22], sizeof(char) * 2);
//        numChannels = EXTRACT_16(uint16Buf);
//
//        // Get the sample rate
//        unsigned int sampleRate;
//        memcpy(uint32Buf, &fileBuffer[24], sizeof(char) * 4);
//        sampleRate = EXTRACT_32(uint32Buf);
//
//        // Bit depth of the wav file
//        unsigned int bitDepth;
//        memcpy(uint16Buf, &fileBuffer[16], sizeof(char) * 2);
//        bitDepth = EXTRACT_16(uint16Buf);
//
//        // Start of the data chunk.
//        int dataStart = 20 + subChunk1Size + 4;
//
//        // Size of the sample data
//        unsigned int subchunk2Size;
//        memcpy(uint32Buf, &fileBuffer[dataStart], sizeof(char) * 4);
//        subchunk2Size = EXTRACT_32(uint32Buf);
//
//        int numSamples = (subchunk2Size / numChannels) / (bitDepth / 8);
//
//        _channels = numChannels;
//        _sampleRate = sampleRate;
//        _length = numSamples;
//
//        // Allocate sample buffer
//        _samples = new float[numChannels * numSamples];
//        _buffersAllocated = true;
//
//        unsigned char *wavSamples = fileBuffer + dataStart + 4;
//
//        for(int i=0; i < numSamples; i++)
//        {
//            int sampIdx = i * numChannels * (bitDepth / 8);
//
//            //if(bitDepth == 16) {
//                for(int c=0; c < numChannels; c++) {
//                    unsigned char *sPtr = wavSamples + sampIdx + (c * (bitDepth / 8));
//                    int16_t samp = EXTRACT_16(sPtr);
//                    float halfMax = UINT16_MAX / 2;
//
//                    _samples[(i * numChannels) + c] = (samp - halfMax) / halfMax;
//                }
//            //}
//        }
//
//        delete[] fileBuffer;

        drwav *pWav = drwav_open_file(path.c_str());
        if(pWav == NULL) {
            throw SoundFileException("Unable to open WAV file");
        }

        _samples = (float *)malloc((size_t)pWav->totalSampleCount * sizeof(float));
        _buffersAllocated = true;
        _channels = pWav->channels;
        _length = (int) (pWav->totalSampleCount / _channels);
        _sampleRate = pWav->sampleRate;

        drwav_read_f32(pWav, pWav->totalSampleCount, _samples);
        drwav_close(pWav);
    }
        
}
