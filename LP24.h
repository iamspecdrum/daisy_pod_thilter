/*
  ==============================================================================

    LP24.h
    Created: 4 Feb 2018 3:04:40pm
    Author:  cumbe

  ==============================================================================
*/

#pragma once

#include "math.h"
#define PI 3.14159265
//==============================================================================
/*
*/

class LP24    
{
public:
    LP24():
    cutoff(0.1f),
    resonance(0.0),
    buf0(0.0),
    buf1(0.0),
    buf2(0.0),
    buf3(0.0),
    sampleRate(48000.0f)
    {
       calculateFeedbackAmount();
    }

    ~LP24()
    {
    }
    void Init() {
        cutoff = 750.0;
        resonance = 0.0;
        buf0 = 0.0;
        buf1 = 0.0;
        buf2 = 0.0;
        buf3 = 0.0;
        calculateFeedbackAmount();
    }
    float process(float inputValue){
        buf0 += cutoff * (inputValue - buf0);
        buf1 += cutoff * (buf0 - buf1);
        buf2 += cutoff * (buf1 - buf2);
        buf3 += cutoff * (buf2 - buf3);
    return buf3;
    };
    void set(float newCutoff) {
        if(sampleRate <= 0.0f)
            sampleRate = 48000.0f;

        if(newCutoff <= 0.0f)
            cutoff = 0.0f;
        else
            cutoff = 1.0f - expf(-2.0f * PI * newCutoff / sampleRate);

        cutoff = fminf(0.999f, fmaxf(0.0f, cutoff));
        calculateFeedbackAmount();
    };
    void setResonance(float newResonance){
        resonance = newResonance;
        calculateFeedbackAmount();
    };
    void setSampleRate(float sr){
        sampleRate=sr;
    };
private:
    float cutoff;
    float resonance;
    float feedbackAmount;
    void calculateFeedbackAmount() { 
        feedbackAmount = resonance + resonance/(1.0 - cutoff); 
    };
    float buf0;
    float buf1;
    float buf2;
    float buf3;
    float sampleRate;
};