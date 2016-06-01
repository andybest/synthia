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

#pragma once

#include <vector>
#include <map>
#include "stdint.h"

#include "SynthContext.h"
#include "SynthVoice.h"
#include "SynthiaUtils.h"
#include "WavetableOscillator.h"
#include "Envelope.h"
#include "wavetable_samples.h"
#include "midi.h"
#include "MoogVoice.h"
#include "Delay.h"

namespace Synthia
{

    typedef enum
    {
        kKeyTransitionTypeMonophonicLastPlayed,
        kKeyTransitionTypeLegatoLastPlayed,
        kKeyTransitionTypePolyphonic
    } KeyTransitionType_t;

    enum
    {
        kSynthesizerParameter_Filter_Cutoff,
        kSynthesizerParameter_Filter_Resonance,

        kSynthesizerParameter_FilterEnvelope_Attack,
        kSynthesizerParameter_FilterEnvelope_Decay,
        kSynthesizerParameter_FilterEnvelope_Sustain,
        kSynthesizerParameter_FilterEnvelope_Release,

        kSynthesizerParameter_Delay_Time,
        kSynthesizerParameter_Delay_Feedback,
        kSynthesizerParameter_Delay_Volume,

        kSynthesizerParameter_MasterVolume,

        kSynthesizerParameter_FilterEnvelope_Enable,
        kSynthesizerParameter_HeadphoneVolume,
        kSynthesizerParameter_LegatoEnable,
    };

    void setHeadphoneVolume(int vol);

    class Synthesizer : public Controllable
    {
    public:
        Synthesizer(uint32_t sampleRate);

        ~Synthesizer();
        
        SynthContext synthContext;

        KeyTransitionType_t keyTransitionType();

        void processMidiMessage(MidiMessage_t *msg);

        void addVoice(SynthVoice *voice);

        void addVoiceCCMapping(ControlEntryId id, unsigned char ccControllerNum);

        void processControlChange(unsigned char controllerNumber, unsigned char value);

        void sendControlChangeToVoices(ControlEntryId entryId, unsigned char value);

        void processPitchBend(int pitchBendValue);

        void sendPitchBendToVoices(int pitchBendValue);

        void keyOn(MidiMessage_t *msg);

        void keyOff(MidiMessage_t *msg);

        void changeValueForControlId(ControlEntryId id, float value);

        inline float tick()
        {
            float voiceSamp = 0.0f;

            for (int i = 0; i < _voices.size(); i++)
            {
                voiceSamp += _voices[i]->tick(0);
            }

            if (_enableFilterEnvelope)
            {
                float eTick = _filterEnvelope.tick(0);
                _lowpassFilter.setCutoff(eTick * _filterCutoffMax + 0.01);
            } else
            {
                _lowpassFilter.setCutoff(_filterCutoffMax);
            }

            float filteredSamp = _lowpassFilter.tick(0, voiceSamp);
            return _delay.tick(0, filteredSamp) * _masterVolume;
        }


    private:
        Envelope       _filterEnvelope;
        Lowpass        _lowpassFilter;
        Synthia::Delay _delay;
        float          _filterCutoffMax;
        float          _masterVolume;
        bool           _enableFilterEnvelope;
        int            _pitchBend;

        std::vector<uint8_t> _keyStack;

        std::vector<SynthVoice *>             _voices;
        std::vector<SynthVoice *>             _availableVoices;
        // Voices that are currently being played (keyon)
        std::map<unsigned char, SynthVoice *> _playingVoices;

        std::map<unsigned char, ControlEntryId> _voiceCCMapping;
        std::map<unsigned char, ControlEntryId> _paramCCMapping;

        KeyTransitionType_t _keyTransitionType;

    };

}
