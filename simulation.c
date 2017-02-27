#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>


#include "path_tree.h"

#define ALPHABET "ab"
#define ALPHABET_SIZE  2


//
typedef struct List List;
struct List{
	PathTree *nodePt; // the init path-tree
	List *nextPt;
};

List* pathTreeList; // n会被init成0
static int ptCounter=0 ; //counter for the path-trees 

/* Add a pathtree into the list */
void add_pathtree(List* list, PathTree * pt){
	if(list->nodePt== NULL)
		list->nodePt = pt;
	else{
		List* newList =(List *)malloc(sizeof(List));
		newList->nodePt = pt;
		list->nextPt= newList;
	} 
	ptCounter++;
}



int main(int argc, char **argv){
  printf("Simulation starts...");
  
  char alphabet[ALPHABET_SIZE] = ALPHABET;

  //Fst* fst = (Fst*)malloc(sizeof(Fst));
  char fst[9][2] = {"15","2a","3b","04","8","6a","7c","0",""};

  //generate_fst(fst); // *fix: allocate memory
 
  PathTree* initPt =(PathTree*)malloc(sizeof(PathTree));
  path_tree_init(fst, initPt); // generate the init path-tree
  
  add_pathtree(pathTreeList, initPt);   // add the first path-tree to the list

  List * tempList;
  bool coverage = false;
  char* output;

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


