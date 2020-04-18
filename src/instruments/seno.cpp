#include <iostream>
#include <unistd.h>
#include <iterator>
#include <math.h>
#include "seno.h"
#include "keyvalue.h"

#include <stdlib.h>

using namespace upc;
using namespace std;

seno::seno(const std::string &param): adsr(SamplingRate, param) {
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
  
  //Create a tbl with one period of a sinusoidal wave
  tbl.resize(N);
  float phase = 0, step = 2 * M_PI /(float) N;
  index = 0;
  for (int i=0; i < N ; ++i) {
    tbl[i] = sin(phase);
    //cout << tbl[i] << "\n";
    phase += step;
  }
}


void seno::command(long cmd, long note, long vel) {
  if (cmd == 9) {		//'Key' pressed: attack begins
    bActive = true;
    adsr.start();
    index = 0;
	  A = vel / 127.;
    //adding the note: A
    float f0 = (440.00*pow(2,((float)note-69.00)/12.00))/16000; 
    step = tbl.size()*f0;
  }
  else if (cmd == 8) {	//'Key' released: sustain ends, release begins
    adsr.stop();
  }
  else if (cmd == 0) {	//Sound extinguished without waiting for release to end
    adsr.end();
  }
}


const vector<float> & seno::synthesize() {
  if (not adsr.active()) {
    x.assign(x.size(), 0);
    bActive = false;
    return x;
  }
  else if (not bActive)
    return x;
  
  for (unsigned int i=0; i<x.size(); ++i) {
    if (index == tbl.size())
      index = 0;
    x[i] = 0.5*A * tbl[index*step]; 
    cout << x[i] << "\n";
    index++;
  } 
  adsr(x); //apply envelope to x and update internal status of ADSR

  /*ofstream output_file("/mnt/c/Users/Patron/Desktop/2020 Q2/PAV/LAB/P5/work");
  ostream_iterator<int> output_iterator( output_file, "\n" );
  // Passing all the variables inside the vector from the beginning of the vector to the end.
  copy( x.begin( ), x.end( ), output_iterator );*/

  /*char buffer[256];
  char *val = getcwd(buffer, sizeof(buffer));
  if (val) {
    std::cout << buffer << std::endl;
  }*/
  return x;
}
