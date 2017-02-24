
// Use a pair of chars to represent the transduction on each edge in an FST
typedef struct CharPair {
  char fst; // an epsilon or a symbol from input alphabet
  char snd; // just epsilon or a bit, 0 or 1
} CPair;


typedef struct IntCharPair {
  int fst;
  char snd;
} ICPair;
