#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>


#include "path_tree.h"

#define ALPHABET "ab"
#define ALPHABET_SIZE  2

#define A2I(x) (95-x)  // letters must be ACSII greater than 'a'

#define TEST 1

 // Simplified Thompson FST representation:
  // First column: the left choice, -1 means no outgoing edge,i.e. final state
  // Second column: the right choice or the transition symbol below: 
  // epsilon:-1; 
  // a:-2 
  // b:-3
  // c:-4,
  // i.e: 95 - int(x)
 
 int fst1[9][2] = {{1,5},{2,-2},{3,-3},
  				   {0,4},{8,-1},{6,-2},
  				   {7,-4},{0,-1},{-1,-1}};

  int fst2[17][2] = {{1,8},{2,-1},{3,5},
  					{4,-2},{2,-1},{6,-3},
  					{7,-1},{-1,-1},{9,-1},
  					{10,16},{11,14},{12,-2},
  					{13,-1},{9,-1},{15,-3},
  					{13,-1},{7,-1}};
//
typedef struct List List;
struct List{
	PathTree *nodePt; // the init path-tree
	List *nextPt;
};

List* pathTreeList; 
static int pathtreeCounter=0 ; //counter for the path-trees 

/* Add a pathtree into the list */
void add_pathtree(List* list, PathTree* pt){
	if(!list->nodePt){ // the init path-tree
		list->nodePt = pt;
		list->nextPt = NULL;
	}
	else{
		while(list->nextPt)
			list = list->nextPt;
		List* newList =(List *)malloc(sizeof(List));
		newList->nodePt = pt;
		newList->nextPt = NULL;
		list->nextPt= newList;
	} 
	pathtreeCounter++;
}



int main(int argc, char **argv){
  printf("Simulation starts...\n");
  Fst (*fst)[2] = fst2;

  PathTree* initPt =(PathTree*)malloc(sizeof(PathTree));
  path_tree_init(fst2, initPt); // generate the init path-tree
//#if TEST
  print_pathtree(initPt);
//#endif  

   pathTreeList = (List*)malloc(sizeof(List));
   add_pathtree(pathTreeList, initPt);   // add the first path-tree to the list
// #if TEST
   printf("pathTree counter: %d \n", pathtreeCounter);
// #endif  

//   step_one(initPt, 3,'a', fst);
// #if TEST
//   print_pathtree(initPt);
// #endif
  // printf("first alphabet: %d", A2I(ALPHABET[0]));
  // List * tempList;
  // bool coverage = false;
  // char* output;

  // PathTree* ptPointer = pathTreeList->nodePt;

//   while(!coverage){ // check if the new-generated path-trees are coverd already
//   	while(!ptPointer){ //visit all the path-trees
//   		for(int i=0; i<ALPHABET_SIZE; i++){
// 		  	char symbol = alphabet[i];
// 		  	ICPair* leaves = get_leaves(ptPointer); // get the leaves

// 		  	// remove the branch that has no transition	
// 		  	kill(ptPointer, fst, leaves, symbol); 

// 		  	//extend the tree with the input symbol
// 		  	step(ptPointer,fst, leaves, symbol); 

// 		  	ICPair* newLeaves = get_leaves(ptPointer);
// 		  	while(!newLeaves){ // traverse all the leaves
// 			  	closure(ptPointer, fst, newLeaves->fst);
// 			  	output = contract(ptPointer);
// 			  	newLeaves = newLeaves->next;
// 		  	}
// //		  	prune(ptPointer); //?
//  	 	}
//  	 	add_pathtree(tempList, ptPointer);
//  	 	ptPointer = pathTreeList->nextPt;
// 	}
// 	coverage = is_covered(pathTreeList, tempList);
	// }

}


