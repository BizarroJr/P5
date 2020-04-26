#include <iostream>
#include "instrument_dumb.h"
#include "seno.h"
#include "sinfm1.h"
#include "campana.h"
#include "woodwind.h"
#include "genericins.h"
#include "fagot.h"
#include "kick.h"
#include "guitar.h"
#include "snare.h"

/*
  For each new instrument:
  - Add the header in this file
  - Add the call to the constructor in get_instrument() (also in this file)
  - Add the source file to src/meson.build
*/

using namespace std;

namespace upc {
  Instrument * get_instrument(const string &name,
			      const string &parameters) {
    Instrument * pInst = 0;
    //    cout << name << ": " << parameters << endl;
    if (name == "InstrumentDumb") {
      pInst = (Instrument *) new InstrumentDumb(parameters);
    }
    else if (name == "seno"){
      pInst = (Instrument*) new seno(parameters);
    }
    else if (name == "Sinfm1"){
      pInst = (Instrument*) new Sinfm1(parameters);
    }
    else if (name == "Bell"){
      pInst = (Instrument*) new Bell(parameters);
    }
    else if (name == "Woodwind"){
      pInst = (Instrument*) new Woodwind(parameters);
    }
    else if (name == "genericins"){
      pInst = (Instrument*) new genericins(parameters);
    }
    else if (name == "Fagot") {
      pInst = (Instrument*) new Fagot(parameters);
    }
    else if (name == "Kick") {
      pInst = (Instrument*) new Kick(parameters);
    }
    else if (name == "Guitar") {
      pInst = (Instrument*) new Guitar(parameters);
    }
    else if (name == "Snare") {
      pInst = (Instrument*) new Snare(parameters);
    }
    return pInst;
  }
}
