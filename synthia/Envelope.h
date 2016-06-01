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
#include "Triggerable.h"

#ifndef __Envelope_H_
#define __Envelope_H_

namespace Synthia
{
    typedef enum {
        kEnvelopeIdle = -1,
        kEnvelopePhaseAttack = 0,
        kEnvelopePhaseDecay,
        kEnvelopePhaseSustain,
        kEnvelopePhaseRelease
    } EnvelopeState_t;

    class Envelope : public Generator
    {
    public:
        void init(SynthContext *ctx);
        float tick(int channel);
        void setAttackTime(float attackTime);
        void setDecayTime(float decayTime);
        void setReleaseTime(float releaseTime);
        void setSustainLevel(float sustainLevel);
        void keyOn();
        void keyOff();
        void setRetriggerTime(float retriggerTime);

    private:
        float _timePerTick;
        float _target;
        float _value;
        EnvelopeState_t _state;

        float _attackRate;
        float _decayRate;
        float _sustainLevel;
        float _releaseRate;
        float _releaseLevel;

        float _retriggerTime;
        int _retriggerCount;
        int _retriggerSamples;
        float _invRetriggerSamples;
        float _retriggerStep;
        
        bool _isReleasing;

        
    };
}

#endif //__Envelope_H_



