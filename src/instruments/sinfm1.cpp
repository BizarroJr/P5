#include <iostream>
#include <math.h>
#include "sinfm1.h"
#include "keyvalue.h"
#include <stdlib.h>

using namespace upc;
using namespace std;

Sinfm1::Sinfm1(const std::string &param): adsr(SamplingRate, param) {
  bActive = false;
  x.resize(BSIZE);

  /*
    You can use the class keyvalue to parse "param" and configure your instrument.
    Take a Look at keyvalue.h    
  */
  KeyValue kv(param);
  int N; 
  float I, fm;
  if (!kv.to_int("N",N))
    N = 40; //default value
  
  if (!kv.to_float("I",I))
    I = 1; 
  
  if (!kv.to_float("fm",fm))
    fm = 5;

I = 1. - pow(2, -I / 12.);

  //Create a tbl with one period of a sinusoidal wave
  tbl.resize(N);
  float phase = 0, step = 2 * M_PI /(float) N;
  index = 0;
  for (int i=0; i < N ; ++i) {
    tbl[i] = sin(phase);
    phase += step;
  }
}


void Sinfm1::command(long cmd, long note, long vel) {
  
/*  float inc_fase_mod = 0;
  float fase_mod = 0;*/
  if (cmd == 9) {		//'Key' pressed: attack begins
    bActive = true;
    adsr.start();
    index = 0;
	  A = vel / 127.;
    //adding the note: A
    float f0 = (440.00*pow(2,((float)note-69.00)/12.00))/SamplingRate; 
    step = tbl.size()*f0;
    /*float feme = f0*N2;
    float fdis = f0*N1;
    inc_fase_mod = 2*M_PI*feme; 
    fase_mod = 0;*/
  }
  else if (cmd == 8) {	//'Key' released: sustain ends, release begins
    adsr.stop();
  }
  else if (cmd == 0) {	//Sound extinguished without waiting for release to end
    adsr.end();
  }
}


const vector<float> & Sinfm1::synthesize() {
  float feme = f0*N2;
  float inc_fase_mod = 2*M_PI*feme; 
  float fase_mod = 0;
  
  if (not adsr.active()) {
    x.assign(x.size(), 0);
    bActive = false;
    return x;
  }
  else if (not bActive) {
    return x;
  }
  for (unsigned int i=0; i<x.size(); ++i) {
    if (index*step == tbl.size()){
      index = 0;
    }
    x[i] = 0.2 * A * tbl[index*step];
    index+= (1 + (I*sin(fase_mod)));
    fase_mod += inc_fase_mod;
  }
  adsr(x); //apply envelope to x and update internal status of ADSR

  return x;
}
