/* This file defines the data structure representinga Thompson FST 
 * (or more precisely, an oracle FST in Kleenex)
 */

#include "Utils.h"


// a state in a Thompson FST
typedef struct State {
  int n;       // state number, 
  CPair transl; // transduction on left choice 
  CPair transr; // transduction on right choice
  struct State *outl; // left choice
  struct State *outr; // right choice if any
} State;    
    
typedef struct Fst {
  State *startSt;
  State *stateList;
} Fst;


Fst* generate_fst();


    
