#include <iostream>
#include <math.h>
#include "superdistor.h"
#include "keyvalue.h"

#include <stdlib.h>

using namespace upc;
using namespace std;

//static float SamplingRate = 44100;

Distor::Distor(const std::string &param) {
  fase = 0;

  KeyValue kv(param);

  if (!kv.to_float("A", A))
    A = 1; //Booster per la distorsió (podria estar fent un solo)

  if (!kv.to_float("Th", Th))
    Th = 0.4; //Quantitat de distorsió

}

void Distor::command(unsigned int comm) {
  if (comm == 1) fase = 0;
}

void Distor::operator()(std::vector<float> &x){
  for (unsigned int i = 0; i < x.size(); i++) {
    if(x[i] > Th){
      x[i] = Th;
    }
    else if(x[i] < -Th) {
      x[i] = -Th;
    }
   
    x[i] = A * x[i];   
  }
}
