#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>


#include "path_tree.h"

#define ALPHABET "ab"
#define ALPHABET_SIZE  2

#define A2I(x) (95-x)  // letters must be ACSII greater than 'a'

#define TEST 1
#define NEW_LINE  printf("\n")

 // Simplified Thompson FST representation:
  // First column: the left choice, -1 means no outgoing edge,i.e. final state
  // Second column: the right choice or the transition symbol below: 
  // epsilon:-1; 
  // a:-2 
  // b:-3
  // c:-4,
 
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


List* pathTreeList; 
static int pathtreeCounter=0 ; //counter for the path-trees 


int main(int argc, char **argv){
  printf("Simulation starts...\n");
  
  Fst (*fst)[2] = fst2; // choose a Thompson fst

//  char alphabet[ALPHABET_SIZE] = ALPHABET;
 
  PathTree* initPt =(PathTree*)malloc(sizeof(PathTree));
  path_tree_init(fst, initPt); // generate the init path-tree
#if TEST
  print_pathtree(initPt);
#endif 

  pathTreeList = (List*)malloc(sizeof(List));
  pathTreeList-> nodePt = NULL;
  pathTreeList-> nextPt = NULL;

  add_pathtree(pathTreeList, initPt);   // add the first path-tree to the list
  pathtreeCounter++;
#if TEST
   printf("pathTree counter: %d \n Pathtrees: ", pathtreeCounter);
   print_list(pathTreeList);
   printf("\n");
#endif 

   List* leaves = (List*) malloc(sizeof(List));
   get_leaves(initPt,leaves);
#if TEST
   printf("Leaves of init path-tree: ");
   print_list(leaves); NEW_LINE;
#endif

   step(leaves, fst,'b');
#if TEST
   print_pathtree(initPt); NEW_LINE;
#endif
    contract(initPt);
#if TEST
   print_pathtree(initPt); NEW_LINE;
#endif

printf("input 2nd 'b'\n");
   List* leaves2 = (List*) malloc(sizeof(List));
   get_leaves(initPt,leaves2);
   printf("Leaves of init path-tree: ");
   print_list(leaves2); NEW_LINE;

   step(leaves2, fst,'b');
   contract(initPt);
#if TEST
   print_pathtree(initPt); NEW_LINE;
#endif


  // List * tempList;
  // bool coverage = false;
  // char* output;

//   PathTree* ptPointer = pathTreeList->nodePt;

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
// 	}

}


