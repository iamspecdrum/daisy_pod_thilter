#include <cmath>
#define PI 3.14159265

class L_Riley_LP
{

public:
    L_Riley_LP():
    fc(750.0),
    sampleRate(44100.0)
    {
        wc=2*PI*fc;
        wc2=wc*wc;
        wc3=wc2*wc;
        wc4=wc2*wc2;
        k=wc/tan(PI*fc/sampleRate);
        k2=k*k;
        k3=k2*k;
        k4=k2*k2;
        sqrt2=sqrt(2);
        sq_tmp1=sqrt2*wc3*k;
        sq_tmp2=sqrt2*wc*k3;
        a_tmp=4*wc2*k2+2*sq_tmp1+k4+2*sq_tmp2+wc4;
        b1=(4*(wc4+sq_tmp1-k4-sq_tmp2))/a_tmp;
        b2=(6*wc4-8*wc2*k2+6*k4)/a_tmp;
        b3=(4*(wc4-sq_tmp1+sq_tmp2-k4))/a_tmp;
        b4=(k4-2*sq_tmp1+wc4-2*sq_tmp2+4*wc2*k2)/a_tmp;
    }
    void setSampleRate(float sr){
        sampleRate=sr;
    }
    float process(float inputValue){
        a0=wc4/a_tmp;
        a1=4*wc4/a_tmp;
        a2=6*wc4/a_tmp;
        a3=a1;
        a4=a0;
        tempx=inputValue;
        tempy=a0*tempx+a1*xm1+a2*xm2+a3*xm3+a4*xm4-b1*ym1-b2*ym2-b3*ym3-b4*ym4;
        xm4=xm3;
        xm3=xm2;
        xm2=xm1;
        xm1=tempx;
        ym4=ym3;
        ym3=ym2;
        ym2=ym1;
        ym1=tempy;

        return tempy;
    };

    void set(float newCutoff){
        fc = newCutoff;
    };
private:
    float sampleRate;
    float fc = 0.0f;
    float sqrt2;
    float wc = 0.0f, wc2 = 0.0f, wc3 = 0.0f, wc4 = 0.0f;
    float k = 0.0f, k2 = 0.0f, k3 = 0.0f, k4 = 0.0f;
    float sq_tmp1 = 0.0f, sq_tmp2 = 0.0f;
    float a_tmp = 0.0f;
    float a0 = 0.0f, a1 = 0.0f, a2 = 0.0f, a3 = 0.0f, a4 = 0.0f;
    float b1 = 0.0f, b2 = 0.0f, b3 = 0.0f, b4 = 0.0f;
    float tempx = 0.0f;
    float tempy = 0.0f;
    float xm1 = 0.0f;
    float xm2 = 0.0f;
    float xm3 = 0.0f;
    float xm4 = 0.0f;
    float ym1 = 0.0f, ym2 = 0.0f, ym3 = 0.0f, ym4 = 0.0f;
};
class L_Riley_HP
{

public:
    L_Riley_HP():
    fc(750.0),
    sampleRate(44100.0)
    {
        wc=2*PI*fc;
        wc2=wc*wc;
        wc3=wc2*wc;
        wc4=wc2*wc2;
        k=wc/tan(PI*fc/sampleRate);
        k2=k*k;
        k3=k2*k;
        k4=k2*k2;
        sqrt2=sqrt(2);
        sq_tmp1=sqrt2*wc3*k;
        sq_tmp2=sqrt2*wc*k3;
        a_tmp=4*wc2*k2+2*sq_tmp1+k4+2*sq_tmp2+wc4;
        b1=(4*(wc4+sq_tmp1-k4-sq_tmp2))/a_tmp;
        b2=(6*wc4-8*wc2*k2+6*k4)/a_tmp;
        b3=(4*(wc4-sq_tmp1+sq_tmp2-k4))/a_tmp;
        b4=(k4-2*sq_tmp1+wc4-2*sq_tmp2+4*wc2*k2)/a_tmp;
    }
    void setSampleRate(float sr){
        sampleRate=sr;
    }

    float process(float inputValue){
        a0=k4/a_tmp;
        a1=-4*k4/a_tmp;
        a2=6*k4/a_tmp;
        a3=a1;
        a4=a0;
        tempx=inputValue;

        tempy=a0*tempx+a1*xm1+a2*xm2+a3*xm3+a4*xm4-b1*ym1-b2*ym2-b3*ym3-b4*ym4;
        xm4=xm3;
        xm3=xm2;
        xm2=xm1;
        xm1=tempx;
        ym4=ym3;
        ym3=ym2;
        ym2=ym1;
        ym1=tempy;

        return tempy;
    }
    void set(float newCutoff){
        fc = newCutoff;
    };
private:
    float sampleRate;
    float fc = 0.0f;
    float sqrt2;
    float wc = 0.0f, wc2 = 0.0f, wc3 = 0.0f, wc4 = 0.0f;
    float k = 0.0f, k2 = 0.0f, k3 = 0.0f, k4 = 0.0f;
    float sq_tmp1 = 0.0f, sq_tmp2 = 0.0f;
    float a_tmp = 0.0f;
    float a0 = 0.0f, a1 = 0.0f, a2 = 0.0f, a3 = 0.0f, a4 = 0.0f;
    float b1 = 0.0f, b2 = 0.0f, b3 = 0.0f, b4 = 0.0f;
    float tempx = 0.0f;
    float tempy = 0.0f;
    float xm1 = 0.0f;
    float xm2 = 0.0f;
    float xm3 = 0.0f;
    float xm4 = 0.0f;
    float ym1 = 0.0f, ym2 = 0.0f, ym3 = 0.0f, ym4 = 0.0f;
};
class ThreeBandEQ   
{
public:
  ThreeBandEQ()
  {
    setSampleRate(44100);
    setGains(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
    //setRatios(0.75, 0.75, 0.5, 0.5, 0.25, 0.25),
    setRatios(1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
    setMidHP(20.0);
    setSideHP(125.0);
    setMidLMC(175.0);
    setSideLMC(750.0);
    setMidMHC(2750.0);
    setSideMHC(2750.0);
    setMidLP(10000.0);
    setSideLP(6600.0);
    resetMatch();
    reset();
    setGoals(0.068,0.031,0.039,0.043,0.035,0.038,0.031,0.031,0.031,0.063,0.063,0.063);
  }
  ~ThreeBandEQ()
  {
  }
  void Init() {

    setGains(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
    //setRatios(0.75, 0.75, 0.5, 0.5, 0.25, 0.25),
    setRatios(1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
    setMidHP(20.0);
    setSideHP(125.0);
    setMidLMC(175.0);
    setSideLMC(750.0);
    setMidMHC(2750.0);
    setSideMHC(2750.0);
    setMidLP(10000.0);
    setSideLP(6600.0);
    setGoals(0.068,0.031,0.039,0.043,0.035,0.038,0.031,0.031,0.031,0.063,0.063,0.063);
  }
  void setMidHP(float freq) {
    midHP.set(freq);
  }
  void setSideHP(float freq) {
    leftHP.set(freq);
    rightHP.set(freq);
  }
  void setMidLP(float freq) {
    midLP.set(freq);
  }
  void setSideLP(float freq) {
    leftLP.set(freq);
    rightLP.set(freq);
  }
  void setMidLMC(float freq){
    midLPL.set(freq);
    midHPM.set(freq);
  }
  void setSideLMC(float freq){
    leftLPL.set(freq);
    rightLPL.set(freq);
    leftHPM.set(freq);
    rightHPM.set(freq);
  }
  
  void setMidMHC(float freq){
    midLPM.set(freq);
    midHPH.set(freq);
  }
  void setSideMHC(float freq){
    leftLPM1.set(freq);
    leftLPM2.set(freq);
    rightLPM1.set(freq);
    rightLPM2.set(freq);
    leftHPH.set(freq);
    rightHPH.set(freq);
  }
  
  float mid(float left, float right){
    return (left+right)/2.0;
  }
  
  float leftOnly(float left, float right){
    return left-mid(left,right);
  }
  
  float rightOnly(float left, float right){
    return right-mid(left,right);
  }
  void reset() {
    leftlowtmp = 0;
    leftmidtmp = 0;
    lefthightmp = 0;
    midlowtmp = 0;
    midmidtmp = 0;
    midhightmp = 0;
    rightlowtmp = 0;
    rightmidtmp = 0;
    righthightmp = 0;
    sidelowrms = 0;
    sidemidrms = 0;
    sidehighrms = 0;
    midlowrms = 0;
    midmidrms = 0;
    midhighrms = 0;
    sidelowsd = 0;
    sidemidsd = 0;
    sidehighsd = 0;
    m=0;
    l = 0;
    r = 0;
    midh = 0;
    midm = 0;
    midl = 0;
    lefth = 0;
    leftm = 0;
    leftl = 0;
    righth = 0;
    rightm = 0;
    rightl = 0;
    plhrms = 0;
    plmrms = 0;
    pllrms = 0;
    pmhrms = 0;
    pmmrms = 0;
    pmlrms = 0;
    prhrms = 0;
    prmrms = 0;
    prlrms = 0;
    plhsd = 0;
    plmsd = 0;
    pllsd = 0;
    pmhsd = 0;
    pmmsd = 0;
    pmlsd = 0;
    prhsd = 0;
    prmsd = 0;
    prlsd = 0;
    for (int i = 0; i < 8; i++) {
      processlefthigh[i] = 0.0;
      processleftmid[i] = 0.0;
      processleftlow[i] = 0.0;
      processmidhigh[i] = 0.0;
      processmidmid[i] = 0.0;
      processmidlow[i] = 0.0;
      processrighthigh[i] = 0.0;
      processrightmid[i] = 0.0;
      processrightlow[i] = 0.0;
    };
    index = 0;
  }
  void setGains(float m, float s,float hm,float mm, float lm, float hs, float ms, float ls){
    midGain=m;
    sideGain=s;
    highMidGain=hm;
    midMidGain=mm;
    lowMidGain=lm;
    highSideGain=hs;
    midSideGain=ms;
    lowSideGain=ls;
  }
  void setRatios(float hm, float mm, float lm, float hs, float ms, float ls) {
    highMidRatio = hm;
  
    midMidRatio = mm;
    lowMidRatio = lm;
    highSideRatio = hs;
    midSideRatio = ms;
    lowSideRatio = ls;
  }
  void setSampleRate(float sr){
    leftLPL.setSampleRate(sr);
    rightLPL.setSampleRate(sr);
    midLPL.setSampleRate(sr);
    leftLPM1.setSampleRate(sr);
    leftLPM2.setSampleRate(sr);
    rightLPM1.setSampleRate(sr);
    rightLPM2.setSampleRate(sr);
    midLPM.setSampleRate(sr);
    leftLP.setSampleRate(sr);
    rightLP.setSampleRate(sr);
    midLP.setSampleRate(sr);
    leftHPM.setSampleRate(sr);
    rightHPM.setSampleRate(sr);
    midHPM.setSampleRate(sr);
    leftHPH.setSampleRate(sr);
    rightHPH.setSampleRate(sr);
    midHPH.setSampleRate(sr);

  }
  
  
  void runStats(float* left, float*right, int length) {
    for (int i=0; i<length; i++){
      m = midHP.process(midLP.process(mid(left[i], right[i])));
      l = leftHP.process(leftOnly(left[i], right[i]));
      r = rightHP.process(rightOnly(left[i], right[i]));
      midh = midHPH.process(m);
      midm = midHPM.process(midLPM.process(m));
      midl = midLPL.process((m));
      lefth = leftHPH.process(l);
      leftm = leftHPM.process(leftLPM1.process(l));
      leftl = leftLPL.process((l));
      righth = rightHPH.process(r);
      rightm = rightHPM.process(rightLPM1.process(r));
      rightl = rightLPL.process((r));
      sidehighrms += (abs(lefth)+abs(righth)) / (2.0*length);
      sidemidrms += (abs(leftm)+abs(rightm)) / (2.0*length);
      sidelowrms += (abs(leftl)+abs(rightl)) / (2.0*length);
      midhighrms += (abs(midh) / length);
      midmidrms += (abs(midm) / length);
      midlowrms += (abs(midl) / length);
      maximum = std::fmax(std::fabs(left[i]),std::fabs(right[i]));
    }
    for (int i = 0; i < length; i++) {
      sidehighsd += abs(abs(lefth) + abs(righth) - (2 * sidehighrms)) / (2.0*length);
      sidemidsd += abs(abs(leftm) + abs(rightm) - (2 * sidemidrms)) / (2.0*length);
      sidelowsd += abs(abs(leftl) + abs(rightl) - (2 * sidelowrms)) / (2.0*length);
      midhighsd += abs(abs(midh) - sidehighrms) / length;
      midmidsd += abs(abs(midm) - midmidrms) / length;
      midlowsd += abs(abs(midl) - midlowrms) / length;
    };
  };
  void setGoals(float gmhrms, float gmmrms, float gmlrms, float gshrms, float gsmrms, float gslrms, float gmhsd, float gmmsd, float gmlsd, float gshsd, float gsmsd, float gslsd ) {
    
    midhighrms = gmhrms;
    midmidrms = gmmrms;
    midlowrms = gmlrms;
    sidehighrms = gshrms;
    sidemidrms = gsmrms;
    sidelowrms = gslrms;
    midhighsd = gmhsd;
    midmidsd = gmmsd;
    midlowsd = gmlsd;
    sidehighsd = gshsd;
    sidemidsd = gsmsd;
    sidelowsd = gslsd;
    
  }
  float* match(float left, float right) {
    l = leftHP.process(leftOnly(left, right));
    m = midHP.process(midLP.process(mid(left, right)));
    r = rightHP.process(rightOnly(left, right));
    
    lefth = leftHPH.process(l);
    leftm = leftHPM.process(leftLPM1.process(l));
    leftl = leftLPL.process(l);
    midh = midHPH.process(m);
    midm = midHPM.process(midLPM.process(m));
    midl = midLPL.process(m);
    righth = rightHPH.process(r);
    rightm = rightHPM.process(rightLPM1.process(r));
    rightl = rightLPL.process(r);
    
    if(index<8){
      processlefthigh[index] = lefth;
      processleftmid[index] = leftm;
      processleftlow[index] = leftl;
      processmidhigh[index] = midh;
      processmidmid[index] = midm;
      processmidlow[index] = midl;
      processrighthigh[index] = righth;
      processrightmid[index] = rightm;
      processrightlow[index] = rightl;
      plhrms += abs(lefth) / 8.0;
      plmrms += abs(leftm) / 8.0;
      pllrms += abs(leftl) / 8.0;
      pmhrms += abs(midh) / 8.0;
      pmmrms += abs(midm) / 8.0;
      pmlrms += abs(midl) / 8.0;
      prhrms += abs(righth) / 8.0;
      prmrms += abs(rightm) / 8.0;
      prlrms += abs(rightl) / 8.0;
      
      index++;
    }
    else {
      
      for (int i = 0; i < 8; i++) {
        plhsd += abs(processlefthigh[i] - plhrms) / 8.0;
        plmsd += abs(processleftmid[i] - plmrms) / 8.0;
        pllsd += abs(processleftlow[i] - pllrms) / 8.0;
        pmhsd += abs(processmidhigh[i] - pmhrms) / 8.0;
        pmmsd += abs(processmidmid[i] - pmmrms) / 8.0;
        pmlsd += abs(processmidlow[i] - pmlrms) / 8.0;
        prhsd += abs(processrighthigh[i] - prhrms) / 8.0;
        prmsd += abs(processrightmid[i] - prmrms) / 8.0;
        prlsd += abs(processrightlow[i] - prlrms) / 8.0;
      }
    }
    auto safeRatio = [](float numerator, float denominator) -> float {
      const float eps = 1.0e-9f;
      if(std::fabs(numerator) < eps || std::fabs(denominator) < eps)
        return 1.0f;
      return numerator / denominator;
    };

    const float midHighRatio = safeRatio(midhighsd, pmhsd);
    const float midMidRatio  = safeRatio(midmidsd, pmmsd);
    const float midLowRatio  = safeRatio(midlowsd, pmlsd);
    const float sideHighRatio = safeRatio(sidehighsd, (plhsd / 2.0f + prhsd / 2.0f));
    const float sideMidRatio  = safeRatio(sidemidsd, (plmsd / 2.0f + prmsd / 2.0f));
    const float sideLowRatio  = safeRatio(sidelowsd, (pllsd / 2.0f + prlsd / 2.0f));

    setGains(1.0f,
             0.25f,
             midHighRatio,
             midMidRatio,
             midLowRatio,
             sideHighRatio,
             sideMidRatio,
             sideLowRatio);

    midh = matchBox(midh, pmhrms, midhighrms, midhighsd, pmhsd);
    midm = matchBox(midm, pmmrms, midmidrms, midmidsd, pmmsd);
    midl = matchBox(midl, pmlrms, midlowrms, midlowsd, pmlsd);
    lefth = matchBox(lefth, plhrms, sidehighrms, sidehighsd, plhsd);
    leftm = matchBox(leftm, plmrms, sidemidrms, sidemidsd, plmsd);
    leftl = matchBox(leftl, pllrms, sidelowrms, sidelowsd, pllsd);
    righth = matchBox(righth, prhrms, sidehighrms, sidehighsd, prhsd);
    rightm = matchBox(rightm, prmrms, sidemidrms, sidemidsd, prmsd);
    rightl = matchBox(rightl, prlrms, sidelowrms, sidelowsd, prlsd);
    resetMatch();
    
    
    output[0] = (highMidGain*(midh) + midMidGain * (midm) + lowMidGain * (midl))*midGain + (highSideGain * (lefth) + midSideGain * (leftm) + lowSideGain * (leftl))*sideGain;
    output[1] = (highMidGain*(midh) + midMidGain * (midm) + lowMidGain * (midl))*midGain + (highSideGain * (righth) + midSideGain * (rightm) + lowSideGain * (rightl))*sideGain;
    
    return output;
  };
  void resetMatch() {
    for (int i=0; i<8; i++){
      processlefthigh[i] = 0.0;
      processleftmid[i] = 0.0;
      processleftlow[i] = 0.0;
      processmidhigh[i] = 0.0;
      processmidmid[i] = 0.0;
      processmidlow[i] = 0.0;
      processrighthigh[i] = 0.0;
      processrightmid[i] = 0.0;
      processrightlow[i] = 0.0;
    }
    
    plhrms = 0.5;
    plmrms = 0.5;
    pllrms = 0.5;
    pmhrms = 0.5;
    pmmrms = 0.5;
    pmlrms = 0.5;
    prhrms = 0.5;
    prmrms = 0.5;
    prlrms = 0.5;
    plhsd = 0.25;
    plmsd = 0.25;
    pllsd = 0.25;
    pmhsd = 0.25;
    pmmsd = 0.25;
    pmlsd = 0.25;
    prhsd = 0.25;
    prmsd = 0.25;
    prlsd = 0.25;
    index = 0;
  }
  float matchBox(float input, float originalRms, float targetRms, float sd1, float sd2) {
  
    if(targetRms>originalRms){
      if(input>0.0){
        return input-originalRms*sd1/sd2+targetRms;
      }
      else if(input<0.0){
        return input+originalRms*sd1/sd2-targetRms;
      }
      
      else{
        return input;
      }
    }
    else if(targetRms<originalRms){
      if(input>originalRms){
        return input-originalRms*sd1/sd2+targetRms;
      }
      else if(input<(-1.0)*(originalRms)){
        return input+originalRms*sd1/sd2-targetRms;
      }
      else{
        return input;
      }
    }
    else{
      return input;
    }
    
  }
  
  float midGain;
  float sideGain;
  float midLMC;
  float sideLMC;
  float midMHC;
  float sideMHC;
  float midLPF;
  float sideLPF;
  float m;
  float l;
  float r;
  float midh;
  float midm;
  float midl;
  float lefth;
  float leftm;
  float leftl;
  float righth;
  float rightm;
  float rightl;
  float highMidGain;
  float highSideGain;
  float midMidGain;
  float midSideGain;
  float lowMidGain;
  float lowSideGain;
  float highMidRatio;
  float highSideRatio;
  float midMidRatio;
  float midSideRatio;
  float lowMidRatio;
  float lowSideRatio;
  float output[2];
  float leftlowtmp;
  float leftmidtmp;
  float lefthightmp;
  float midlowtmp;
  float midmidtmp;
  float midhightmp;
  float rightlowtmp;
  float rightmidtmp;
  float righthightmp;
  float sidelowrms;
  float sidemidrms;
  float sidehighrms;
  float midlowrms;
  float midmidrms;
  float midhighrms;
  float sidelowsd;
  float sidemidsd;
  float sidehighsd;
  float midlowsd;
  float midmidsd;
  float midhighsd;
  float processlefthigh[8];
  float processleftmid[8];
  float processleftlow[8];
  float processmidhigh[8];
  float processmidmid[8];
  float processmidlow[8];
  float processrighthigh[8];
  float processrightmid[8];
  float processrightlow[8];
  float plhrms;
  float plmrms;
  float pllrms;
  float pmhrms;
  float pmmrms;
  float pmlrms;
  float prhrms;
  float prmrms;
  float prlrms;
  float plhsd;
  float plmsd;
  float pllsd;
  float pmhsd;
  float pmmsd;
  float pmlsd;
  float prhsd;
  float prmsd;
  float prlsd;
  float maximum;
  int index;
private:
  L_Riley_LP leftLPL;
  L_Riley_LP rightLPL;
  L_Riley_LP midLPL;
  
  L_Riley_LP leftLPM1;
  L_Riley_LP leftLPM2;
  L_Riley_LP rightLPM1;
  L_Riley_LP rightLPM2;
  L_Riley_LP midLPM;
  
  L_Riley_LP leftLP;
  L_Riley_LP rightLP;
  L_Riley_LP midLP;
  
  L_Riley_HP midHP;
  L_Riley_HP leftHP;
  L_Riley_HP rightHP;
  
  L_Riley_HP leftHPM;
  L_Riley_HP rightHPM;
  L_Riley_HP midHPM;
  
  L_Riley_HP leftHPH;
  L_Riley_HP rightHPH;
  L_Riley_HP midHPH;

};