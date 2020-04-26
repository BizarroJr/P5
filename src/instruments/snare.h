#ifndef SNARE
#define SNARE

#include <vector>
#include <string>
#include "instrument.h"
#include "envelope_adsr.h"

namespace upc {
  class Snare: public upc::Instrument {
    EnvelopeADSR adsr;
    unsigned int index;
    double alfa, beta, teta, phi;
        float Aout, N1, N2, fc, fmod, cm, fm, vel, d, A;
    std::vector<float> tbl;
  public:
    Snare(const std::string &param = "");
    void command(long cmd, long note, long velocity=1); 
    const std::vector<float> & synthesize();
    bool is_active() const {return bActive;} 
  };
}

#endif
