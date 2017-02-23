/* This file defines the data structure representinga Thompson FST 
 * (or more precisely, an oracle FST in Kleenex)
 */

//#include <stdio.h>

// Use a pair of chars to represent the transduction on each edge in an FST
typedef struct Pair {
  char fst; // an epsilon or a symbol from input alphabet
  char snd; // just epsilon or a bit, 0 or 1
} Pair;


// a state in a Thompson FST
typedef struct State {
  int n;       // state number, 
  Pair transl; // transduction on left choice 
  Pair transr; // transduction on right choice
  struct State *outl; // left choice
  struct State *outr; // right choice if any
} State;    
    
typedef struct Fst {
  State *startSt;
  State *stateList;
} Fst;


Fst* generate_fst();


    
