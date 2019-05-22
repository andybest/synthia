//
// Created by andybest on 21/05/19.
//

#pragma once

#include "Generator.h"

namespace Synthia {
class PolyBlepOscillator : public PitchedGenerator {

public:
    enum OscillatorMode {
      kOscillatorModeSine,
      kOscillatorModeSaw,
      kOscillatorModeSquare,
      kOscillatorModeTriangle
    };

    PolyBlepOscillator() : lastOutput_(0.0) {}
    double tick() override;
    Frames& tick(Frames& frames) override;
    void init(SynthContext* ctx) override;

    void setMode(OscillatorMode mode);
    void setFrequency(float freq) override;


private:
    double polyBlep(double t);
    double aliasedWaveFormForMode(OscillatorMode mode);

    OscillatorMode mode_;
    float          sampleRate_;
    double         phaseIncrement_;
    double         phase_;
    double         lastOutput_;
};
}
