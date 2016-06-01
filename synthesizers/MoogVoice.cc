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

#include "MoogVoice.h"

#include "wavetable_samples.h"
#include <math.h>

namespace Synthia {
    
    void MoogVoice::init(SynthContext *ctx)
    {
        _ctx = ctx;
        
        _osc1.init(_ctx);
        _osc2.init(_ctx);
        _osc3.init(_ctx);
        
        _osc1.addWavetable(wavetable_triangle, wavetable_triangle_len);
        _osc2.addWavetable(wavetable_triangle, wavetable_triangle_len);
        _osc3.addWavetable(wavetable_triangle, wavetable_triangle_len);
        
        _osc1.addWavetable(wavetable_ramp, wavetable_ramp_len);
        _osc2.addWavetable(wavetable_ramp, wavetable_ramp_len);
        _osc3.addWavetable(wavetable_ramp, wavetable_ramp_len);
        
        _osc1.addWavetable(wavetable_pulse, wavetable_pulse_len);
        _osc2.addWavetable(wavetable_pulse, wavetable_pulse_len);
        _osc3.addWavetable(wavetable_pulse, wavetable_pulse_len);
        
        _osc1.selectWavetable(1);
        _osc2.selectWavetable(1);
        _osc3.selectWavetable(1);
        
        _envelope.init(_ctx);
        _envelope.setAttackTime(0.2);
        _envelope.setReleaseTime(1.0);
        _envelope.setSustainLevel(1.0);
        
        _osc1Volume = 0.66f;
        _osc2Volume = 0.66f;
        _osc3Volume = 0.66f;
        
        _pitchBend = 0;
        
        setupControlEntries();
    }
    
    void MoogVoice::setupControlEntries()
    {
        addControlEntry(kMoogVoiceParameter_OSC1_Waveform, "OSC1 Waveform", kControlTypeFloatZeroOne);
        addControlEntry(kMoogVoiceParameter_OSC1_Volume, "OSC1 Volume", kControlTypeFloatZeroOne);
        addControlEntry(kMoogVoiceParameter_OSC1_Tune, "OSC1 Tune", kControlTypeFloatCustomRange, -24.0f, 24.0f);
        addControlEntry(kMoogVoiceParameter_OSC1_FineTune, "OSC1 FineTune", kControlTypeFloatCustomRange, -100.0f, 100.0f);
        
        addControlEntry(kMoogVoiceParameter_OSC2_Waveform, "OSC2 Waveform", kControlTypeFloatZeroOne);
        addControlEntry(kMoogVoiceParameter_OSC2_Volume, "OSC2 Volume", kControlTypeFloatZeroOne);
        addControlEntry(kMoogVoiceParameter_OSC2_Tune, "OSC2 Tune", kControlTypeFloatCustomRange, -24.0f, 24.0f);
        addControlEntry(kMoogVoiceParameter_OSC2_FineTune, "OSC2 FineTune", kControlTypeFloatCustomRange, -100.0f, 100.0f);
        
        addControlEntry(kMoogVoiceParameter_OSC3_Waveform, "OSC3 Waveform", kControlTypeFloatZeroOne);
        addControlEntry(kMoogVoiceParameter_OSC3_Volume, "OSC3 Volume", kControlTypeFloatZeroOne);
        addControlEntry(kMoogVoiceParameter_OSC3_Tune, "OSC3 Tune", kControlTypeFloatCustomRange, -24.0f, 24.0f);
        addControlEntry(kMoogVoiceParameter_OSC3_FineTune, "OSC3 FineTune", kControlTypeFloatCustomRange, -100.0f, 100.0f);
        
        addControlEntry(kMoogVoiceParameter_Envelope_Attack, "Envelope Attack", kControlTypeFloatCustomRange, 0.0f, 2.0f);
        addControlEntry(kMoogVoiceParameter_Envelope_Decay, "Envelope Decay", kControlTypeFloatCustomRange, 0.0f, 2.0f);
        addControlEntry(kMoogVoiceParameter_Envelope_Sustain, "Envelope Sustain", kControlTypeFloatZeroOne);
        addControlEntry(kMoogVoiceParameter_Envelope_Release, "Envelope Release", kControlTypeFloatCustomRange, 0.0f, 2.0f);
    }
    
    void MoogVoice::changeValueForControlId(ControlEntryId id, float value)
    {
        switch(id) {
                
                /* OSC 1 */
            case kMoogVoiceParameter_OSC1_Waveform:
                _osc1.selectWavetableFloat(value);
                break;
                
            case kMoogVoiceParameter_OSC1_Volume:
                _osc1Volume = value;
                break;
                
            case kMoogVoiceParameter_OSC1_Tune:
                _osc1Tune = roundf(value);
                printf("Tune = %f\n", _osc1Tune);
                calcFrequencies(_frequency);
                break;
                
            case kMoogVoiceParameter_OSC1_FineTune:
                _osc1FineTune = value;
                calcFrequencies(_frequency);
                break;
                
                /* OSC 2 */
            case kMoogVoiceParameter_OSC2_Waveform:
                _osc2.selectWavetableFloat(value);
                break;
                
            case kMoogVoiceParameter_OSC2_Volume:
                _osc2Volume = value;
                break;
                
            case kMoogVoiceParameter_OSC2_Tune:
                _osc2Tune = roundf(value);
                calcFrequencies(_frequency);
                break;
                
            case kMoogVoiceParameter_OSC2_FineTune:
                _osc2FineTune = value;
                calcFrequencies(_frequency);
                break;
                
                /* OSC 3 */
            case kMoogVoiceParameter_OSC3_Waveform:
                _osc3.selectWavetableFloat(value);
                break;
                
            case kMoogVoiceParameter_OSC3_Volume:
                _osc3Volume = value;
                break;
                
            case kMoogVoiceParameter_OSC3_Tune:
                _osc3Tune = roundf(value);
                calcFrequencies(_frequency);
                break;
                
            case kMoogVoiceParameter_OSC3_FineTune:
                _osc3FineTune = value;
                calcFrequencies(_frequency);
                break;
        
                /* ENVELOPE */
            case kMoogVoiceParameter_Envelope_Attack:
                _envelope.setAttackTime(value);
                break;
                
            case kMoogVoiceParameter_Envelope_Decay:
                _envelope.setDecayTime(value);
                break;
                
            case kMoogVoiceParameter_Envelope_Sustain:
                _envelope.setSustainLevel(value);
                break;
                
            case kMoogVoiceParameter_Envelope_Release:
                _envelope.setReleaseTime(value);
                break;
        }
    }
    
    void MoogVoice::processPitchBend(int pitchBendValue)
    {
        _pitchBend = pitchBendValue;
        calcFrequencies(_frequency);
    }
    
    void MoogVoice::calcFrequencies(float baseFreq)
    {
        // Pitch bend values are in steps
        float pitchBendSteps = (_pitchBend / 8192.0f) * 2.0f;
        
        float osc1Freq = SynthiaUtils::tuneFrequencyBySteps(baseFreq, _osc1Tune + pitchBendSteps);
        osc1Freq = SynthiaUtils::tuneFrequencyByCents(osc1Freq, _osc1FineTune);
        _osc1.setFrequency(osc1Freq);
        
        float osc2Freq = SynthiaUtils::tuneFrequencyBySteps(baseFreq, _osc2Tune + pitchBendSteps);
        osc2Freq = SynthiaUtils::tuneFrequencyByCents(osc2Freq, _osc2FineTune);
        _osc2.setFrequency(osc2Freq);
        
        float osc3Freq = SynthiaUtils::tuneFrequencyBySteps(baseFreq, _osc3Tune + pitchBendSteps);
        osc3Freq = SynthiaUtils::tuneFrequencyByCents(osc3Freq, _osc3FineTune);
        _osc3.setFrequency(osc3Freq);
    }
    
    void MoogVoice::setFrequency(float freq)
    {
        _frequency = freq;
        calcFrequencies(_frequency);
    }
    
    void MoogVoice::keyOn()
    {
        _envelope.keyOn();
    }
    
    void MoogVoice::keyOff()
    {
        _envelope.keyOff();
    }    
    
}