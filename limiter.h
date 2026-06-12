#pragma once

#include "math.h"

class DefaultLimiter
{
public:
    DefaultLimiter()
    : threshold(0.95f),
      attack(0.002f),
      release(0.08f),
      env(0.0f),
      gain(1.0f),
      sampleRate(48000.0f)
    {
    }

    ~DefaultLimiter()
    {
    }
    void Init() {
        threshold = 0.95f;
        attack = 0.002f;
        release = 0.08f;
        env = 0.0f;
        gain = 1.0f;
        sampleRate = 48000.0f;
    }
    float process(float inputValue)
    {
        float inputAbs = fabsf(inputValue);

        if(inputAbs > env)
            env += attack * (inputAbs - env);
        else
            env += release * (inputAbs - env);

        float targetGain = 1.0f;
        if(env > threshold)
            targetGain = threshold / env;

        if(targetGain < 0.0f)
            targetGain = 0.0f;

        if(targetGain > gain)
            gain += attack * (targetGain - gain);
        else
            gain += release * (targetGain - gain);

        float output = inputValue * gain;

        // Soft clip to keep peaks from overshooting after gain reduction.
        if(output > 1.0f)
            output = 1.0f - expf(-output);
        else if(output < -1.0f)
            output = -1.0f + expf(output);

        return output;
    }

    void set(float newThreshold)
    {
        threshold = newThreshold;
    }

    void setThreshold(float newThreshold)
    {
        threshold = newThreshold;
    }

    void setAttack(float newAttack)
    {
        attack = newAttack;
    }

    void setRelease(float newRelease)
    {
        release = newRelease;
    }

    void setSampleRate(float sr)
    {
        sampleRate = sr;
    }

private:
    float threshold;
    float attack;
    float release;
    float env;
    float gain;
    float sampleRate;
};
