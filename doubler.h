#pragma once

#include "math.h"

class AudioDoubler
{
public:
    AudioDoubler()
    : delayMs(4.0f),
      feedback(0.25f),
      wetMix(0.0f),
      dryMix(1.0f),
      sampleRate(48000.0f),
      delaySamples(192),
      delaySamplesAlt(193),
      writeIndex(0),
      writeIndexAlt(0)
    {
        Init();
    }

    ~AudioDoubler()
    {
    }

    void Init()
    {
        delayMs = 4.0f;
        feedback = 0.25f;
        wetMix = 0.0f;
        dryMix = 1.0f;
        sampleRate = 48000.0f;

        for(int i = 0; i < kMaxDelaySamples; ++i)
        {
            buffer[i] = 0.0f;
            bufferAlt[i] = 0.0f;
        }

        writeIndex = 0;
        writeIndexAlt = 0;
        updateDelay();
    }

    float process(float inputValue)
    {
        if(delaySamples < 1)
            updateDelay();

        const int readIndex = (writeIndex + (kMaxDelaySamples - delaySamples))
                              % kMaxDelaySamples;
        const int readIndexAlt
            = (writeIndexAlt + (kMaxDelaySamples - delaySamplesAlt))
              % kMaxDelaySamples;

        const float delayed0 = buffer[readIndex];
        const float delayed1 = bufferAlt[readIndexAlt];

        const float wet = (delayed0 * 0.55f) + (delayed1 * 0.45f);
        const float output = (inputValue * dryMix) + (wet * wetMix);

        buffer[writeIndex] = inputValue + (feedback * delayed0);
        bufferAlt[writeIndexAlt] = inputValue + (feedback * delayed1);

        writeIndex = (writeIndex + 1) % kMaxDelaySamples;
        writeIndexAlt = (writeIndexAlt + 1) % kMaxDelaySamples;

        return output;
    }

    void set(float newDelayMs)
    {
        delayMs = newDelayMs;
        updateDelay();
    }

    void setMix(float newMix)
    {
        wetMix = fminf(1.0f, fmaxf(0.0f, newMix));
        dryMix = 1.0f - wetMix;
    }

    void setFeedback(float newFeedback)
    {
        feedback = fminf(0.95f, fmaxf(0.0f, newFeedback));
    }

    void setSampleRate(float sr)
    {
        if(sr <= 0.0f)
            sr = 48000.0f;

        sampleRate = sr;
        updateDelay();
    }

private:
    static const int kMaxDelaySamples = 4096;

    float delayMs;
    float feedback;
    float wetMix;
    float dryMix;
    float sampleRate;

    int delaySamples;
    int delaySamplesAlt;
    int writeIndex;
    int writeIndexAlt;

    float buffer[kMaxDelaySamples];
    float bufferAlt[kMaxDelaySamples];

    void updateDelay()
    {
        if(sampleRate <= 0.0f)
            sampleRate = 48000.0f;

        delaySamples = static_cast<int>(sampleRate * (delayMs * 0.001f));
        if(delaySamples < 1)
            delaySamples = 1;
        if(delaySamples >= kMaxDelaySamples)
            delaySamples = kMaxDelaySamples - 1;

        delaySamplesAlt = delaySamples + 1;
        if(delaySamplesAlt >= kMaxDelaySamples)
            delaySamplesAlt = kMaxDelaySamples - 1;
    }
};
