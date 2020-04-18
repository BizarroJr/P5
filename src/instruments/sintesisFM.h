#ifndef SINTESISFM
#define SINTESISFM

#include <vector>
#include <string>
#include "instrument.h"
#include "envelope_adsr.h"

namespace upc {
  class sintesisFM: public upc::Instrument {
    EnvelopeADSR adsr;
    unsigned int index;
    float A, fo,vel;
    double fase_mod, inc_fase_mod;
    float step, N, N1, N2, I, fm,mod_c,phase, phase_m, alpha_m;
    std::vector<float> tbl;
  public:
    sintesisFM(const std::string &param = "");
    void command(long cmd, long note, long velocity=1); 
    const std::vector<float> & synthesize();
    bool is_active() const {return bActive;} 
  };
}

#endif