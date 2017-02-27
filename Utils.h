
// Use a pair of chars to represent the transduction on each edge in an FST
typedef struct CharPair {
  char in; // an epsilon or a symbol from input alphabet
  char out; // just epsilon or a bit, 0 or 1
} CPair;

//leaf
typedef struct IntCharPair {
  int fst;
  char snd;
  struct IntCharPair * next;
} ICPair;
