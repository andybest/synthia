//
// Created by andybest on 21/05/19.
//

#include <math.h>
#include "PolyBlepOscillator.h"

namespace Synthia {

void PolyBlepOscillator::init(Synthia::SynthContext* ctx) {
    this->_ctx = ctx;
}

double PolyBlepOscillator::tick() {
        double value;
        double t     = phase_ / (M_PI * 2);

        if (mode_ == kOscillatorModeSine) {
            value = aliasedWaveFormForMode(kOscillatorModeSine);
        }
        else if (mode_ == kOscillatorModeSaw) {
            value = aliasedWaveFormForMode(kOscillatorModeSaw);
            value -= polyBlep(t);
        }
        else {
            value = aliasedWaveFormForMode(kOscillatorModeSquare);
            value += polyBlep(t);
            value -= polyBlep(fmod(t + 0.5, 1.0));

            if (mode_ == kOscillatorModeTriangle) {
                value       = phaseIncrement_ * value + (1 - phaseIncrement_) * lastOutput_;
                lastOutput_ = value;
            }
        }

        phase_ += phaseIncrement_;
        while (phase_ > (M_PI * 2)) {
            phase_ -= (M_PI * 2);
        }

        return value;
}

Frames& Synthia::PolyBlepOscillator::tick(Synthia::Frames& frames) {
    for (int i = 0; i < frames.numSamples(); i++) {
        int idx = i * 2;

        auto value = tick();

        for (int c = 0; c < frames.numChannels(); c++) {
            frames[idx + c] = value;
        }
    }

    return frames;
}


double PolyBlepOscillator::polyBlep(double t) {
    double dt = phaseIncrement_ / (M_PI * 2);

    if (t < dt) {
        t /= dt;
        return t + t - t * t - 1.0;
    }
    else if (t > 1.0 - dt) {
        t = (t - 1.0) / dt;
        return t * t + t + t - 1.0;
    }

    return 0;
}

double PolyBlepOscillator::aliasedWaveFormForMode(PolyBlepOscillator::OscillatorMode mode) {
    double value = 0.0;

    switch (mode) {
    case kOscillatorModeSine:value = sin(phase_);
        break;

    case kOscillatorModeSaw:value = (2.0 * phase_ / (M_PI * 2)) - 1.0;
        break;

    case kOscillatorModeSquare:
        if (phase_ < M_PI) {
            value = 1.0;
        }
        else {
            value = -1.0;
        }
        break;

    case kOscillatorModeTriangle:value = -1.0 + (2.0 * phase_ / (M_PI * 2));
        value                          = 2.0 * (fabs(value) - 0.5);
        break;
    }

    return value;
}

void PolyBlepOscillator::setMode(Synthia::PolyBlepOscillator::OscillatorMode mode) {
    mode_ = mode;
}

void PolyBlepOscillator::setFrequency(float freq) {
    _frequency = freq;
    phaseIncrement_ = (double) ((M_PI * 2 * (double)this->_frequency) / (double)_ctx->sampleRate());
}

}
