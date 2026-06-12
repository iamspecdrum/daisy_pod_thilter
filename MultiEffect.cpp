#include "daisysp.h"
#include "daisy_pod.h"
#include "threeEQ.h"
#include "LP24.h"
#include "limiter.h"
#include "doubler.h"
// Set max delay time to 0.75 of samplerate.
#define MAX_DELAY static_cast<size_t>(48000 * 2.5f)
#define THI 1
#define DEL 0


using namespace daisysp;
using namespace daisy;

static DaisyPod pod;

static DelayLine<float, MAX_DELAY> DSY_SDRAM_BSS dell;
static DelayLine<float, MAX_DELAY> DSY_SDRAM_BSS delr;
static ThreeBandEQ threeEq;
static LP24 lp24l, lp24r;
static DefaultLimiter limiterl, limiterr;  
static AudioDoubler doublerEq, doublerOriginal; 
static Parameter deltime, cutoffParam, thilterWet, doublerWet;
int              mode = DEL;

float currentDelay, feedback, delayTarget, cutoff, thilWet, doubWet;



//Helper functions
void Controls();

void GetReverbSample(float &outl, float &outr, float inl, float inr);

void GetDelaySample(float &outl, float &outr, float inl, float inr);

void GetCrushSample(float &outl, float &outr, float inl, float inr);

void GetThreeEqSample(float &outl, float &outr, float inl, float inr);

void AudioCallback(AudioHandle::InterleavingInputBuffer  in,
                   AudioHandle::InterleavingOutputBuffer out,
                   size_t                                size)
{
    float outl, outr, inl, inr;

    Controls();

    //audio
    for(size_t i = 0; i < size; i += 2)
    {
        inl = in[i];
        inr = in[i + 1];

        switch(mode)
        {
            case THI: GetThreeEqSample(outl, outr, inl, inr); break;
            case DEL: GetDelaySample(outl, outr, inl, inr); break;
            default: outl = outr = 0;
        }

        // left out
        out[i] = outl;

        // right out
        out[i + 1] = outr;
    }
}

int main(void)
{
    // initialize pod hardware and oscillator daisysp module
    float sample_rate;

    //Inits and sample rate
    pod.Init();
    pod.SetAudioBlockSize(16);
    sample_rate = pod.AudioSampleRate();
    dell.Init();
    delr.Init();
    threeEq.Init();
    threeEq.setSampleRate(sample_rate);
    lp24l.Init();
    lp24r.Init();
    lp24l.setSampleRate(sample_rate);
    lp24r.setSampleRate(sample_rate);
    limiterl.Init();
    limiterr.Init();
    limiterl.setSampleRate(sample_rate);
    limiterr.setSampleRate(sample_rate);
    doublerEq.Init();
    doublerEq.setSampleRate(sample_rate);
    doublerOriginal.Init();
    doublerOriginal.setSampleRate(sample_rate);



    //set parameters
    deltime.Init(pod.knob1, sample_rate * .05, MAX_DELAY, deltime.LOGARITHMIC);
    doublerWet.Init(pod.knob1, 0, 1, doublerWet.LINEAR);
    thilterWet.Init(pod.knob2, 0, 1, thilterWet.LINEAR);
    cutoffParam.Init(pod.knob2, 200, 20000, cutoffParam.LOGARITHMIC);
    
    

    //delay parameters
    currentDelay = delayTarget = sample_rate * 0.75f;
    dell.SetDelay(currentDelay);
    delr.SetDelay(currentDelay);

    // start callback
    pod.StartAdc();
    pod.StartAudio(AudioCallback);

    while(1) {}
}

void UpdateKnobs(float &k1, float &k2)
{
    k1 = pod.knob1.Process();
    k2 = pod.knob2.Process();

    switch(mode)
    {

        case THI:
            thilWet = thilterWet.Process();
            doubWet = doublerWet.Process();
            cutoff = cutoffParam.Process();
            lp24l.set(cutoff);
            lp24r.set(cutoff);
            break;
        case DEL:
            delayTarget = deltime.Process();
            feedback    = k2;
            break;
        default: break;
    }
}

void UpdateEncoder()
{
    mode = mode + pod.encoder.Increment();
    mode = (mode % 2 + 2) % 2;
}

void UpdateLeds(float k1, float k2)
{
    pod.led1.Set(
        k1 * (mode == 1), k1 * (mode == 0), k1 * (mode == 0 || mode == 1));
    pod.led2.Set(
        k2 * (mode == 1), k2 * (mode == 0), k2 * (mode == 0 || mode == 1    ));

    pod.UpdateLeds(); 
}

void Controls()
{
    float k1, k2;
    delayTarget = feedback = thilWet = doubWet = 0;

    pod.ProcessAnalogControls();
    pod.ProcessDigitalControls();

    UpdateKnobs(k1, k2);

    UpdateEncoder();

    UpdateLeds(k1, k2);
}


void GetDelaySample(float &outl, float &outr, float inl, float inr)
{
    fonepole(currentDelay, delayTarget, .00007f);
    delr.SetDelay(currentDelay);
    dell.SetDelay(currentDelay);
    outl = dell.Read();
    outr = delr.Read();

    dell.Write((feedback * outl) + inl);
    outl = (feedback * outl) + ((1.0f - feedback) * inl);

    delr.Write((feedback * outr) + inr);
    outr = (feedback * outr) + ((1.0f - feedback) * inr);
}

void GetThreeEqSample(float &outl, float &outr, float inl, float inr)
{
    float *eq = threeEq.match(inl, inr);
    doublerEq.setMix(doubWet);
    doublerOriginal.setMix(doubWet);
    float leftEq = eq[0];
    float doublerOutEq = doublerEq.process(leftEq);
    float doublerOutOriginal = doublerOriginal.process(inl);
    //outl = lp24l.process(drywet * inl + (1.0f - drywet) * eq[0]);
    //outr = lp24r.process(drywet * inr + (1.0f - drywet) * eq[1]);
    outl = thilWet*limiterl.process(thilWet*(leftEq)*24.0f) + (1.0f - thilWet)*inl;
    outr = thilWet*limiterr.process(thilWet*(eq[1])*24.0f) + (1.0f - thilWet)*(doublerOutOriginal);
    //outl = lp24l.process(inl);
    //outr = lp24r.process(inr);

}
