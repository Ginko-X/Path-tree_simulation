#include <stdio.h>
#include "FST.h"
#include <stdlib.h>


// generate an FST for test path-tree simulation
// Example from Page 39
void generate_fst(char* fst, int fstSize){
	//char simpleFst[9][2] = {"15","2a","3b","04","8","6a","7c","0",""};
	for(int i=0; i<fstSize;i++){
		for(int j=0; j<2; j++){
			printf("%c\t",&fst[i]);
			fst[i]++;
		}
		printf("\n");
	}
	// State* s = (State*)malloc(sizeof(State));
	// s->transl.out = 0;
	// s->transr.out = 1;
	// soutl = (State*)malloc(sizeof(State));
	// soutr = (State*)malloc(sizeof(State));
	// s->outl = soutl;
	// s->outr = soutr;

	// fst->startSt = 
}

