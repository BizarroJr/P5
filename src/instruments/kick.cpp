#include <iostream>
#include <math.h>
#include "kick.h"
#include "keyvalue.h"
#include <stdlib.h>

using namespace upc;
using namespace std;

Kick::Kick(const std::string &param): adsr(SamplingRate, param) {
  bActive = false;
  x.resize(BSIZE);

  /*
    You can use the class keyvalue to parse "param" and configure your instrument.
    Take a Look at keyvalue.h    
  */
  KeyValue kv(param);
  int N; 

  if (!kv.to_int("N",N))
    N = 40; //default value
  
  if (!kv.to_float("vel",vel))
    vel = 0.5; //Default 
  
  if (!kv.to_float("fm",fm))
    fm = 5; //Default

  
  fc = 80; //Values from the paper
  fmod = 55; 
  N1 = 0;
  N2 = 25;

  cm = fmod/fc;
  //Create a tbl with one period of a sinusoidal wave
  tbl.resize(N);
  float phase = 0, step = 2 * M_PI /(float) N;
  index = 0;
  for (int i=0; i < N ; ++i) {
    tbl[i] = sin(phase);
    phase += step;
  }
}


void Kick::command(long cmd, long note, long vel) {
  if (cmd == 9) {		//'Key' pressed: attack begins
    bActive = true;
    adsr.start();
    index = 0;

	  float f0 = (440.00*pow(2,((float)note-69.00)/12.00));
    float d = f0/SamplingRate; 
    fm = f0*cm;
    float dfm = fm/SamplingRate;
    A = vel/127.0F;

    alfa = 2*M_PI*d;
    beta = 2*M_PI*dfm;
    teta = 0;
    phi = 0;

  }
  else if (cmd == 8) {	//'Key' released: sustain ends, release begins
    adsr.stop();
  }
  else if (cmd == 0) {	//Sound extinguished without waiting for release to end
    adsr.end();
  }
}


const vector<float> & Kick::synthesize() {  
  if (not adsr.active()) {
    x.assign(x.size(), 0);
    bActive = false;
    return x;
  }
  else if (not bActive) {
    return x;
  }
  vector<float> h(x.size(), (N2-N1)*fm);
  adsr(h);
  
  for (unsigned int i=0; i<x.size(); ++i) {
    x[i] = A*sin(teta+(((h[i]+N1*fm)/SamplingRate)*sin(phi)));

    teta+=alfa;
    phi+=beta;
    //Controlamos que esté siempre en la primera vuelta
    //Si dejamos que pase de M_PI se acaba saliendo de los márgenes
    while(teta>M_PI) {
      teta-=2*M_PI;
    }
    while(phi>M_PI) {
      phi-=2*M_PI;
    }
  }
  adsr(x); //apply envelope to x and update internal status of ADSR

  return x;
}
