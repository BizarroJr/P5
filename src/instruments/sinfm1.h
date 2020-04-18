#ifndef SINFM1
#define SINFM1

#include <vector>
#include <string>
#include "instrument.h"
#include "envelope_adsr.h"

namespace upc {
  class Sinfm1: public upc::Instrument {
    EnvelopeADSR adsr;
    unsigned int index;
	    float A, f0, vel;
    float step, N, N1, N2, I, fm;
    std::vector<float> tbl;
  public:
    Sinfm1(const std::string &param = "");
    void command(long cmd, long note, long velocity=1); 
    const std::vector<float> & synthesize();
    bool is_active() const {return bActive;} 
  };
}

#endif
