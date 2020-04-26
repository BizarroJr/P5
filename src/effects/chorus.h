#ifndef CHORUS_H
#define CHORUS_H

#include <vector>
#include <string>
#include "effect.h"

namespace upc {
  class Chorus: public upc::Effect {
    private:
      long double fase_mod, inc_fase_mod;
      long double fase_sen, inc_fase_sen;
	  std::vector<float> buffer;
	  float	fm, I, A;
    public:
      Chorus(const std::string &param = "");
	  void operator()(std::vector<float> &x);
	  void command(unsigned int);
  };
}

#endif
