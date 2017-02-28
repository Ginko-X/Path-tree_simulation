#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>


#include "path_tree.h"

#define ALPHABET "ab"
#define ALPHABET_SIZE  2

#define A2I(x) (95-x)  // letters must be ACSII greater than 'a'
#define NEW_LINE  printf("\n")

#define TEST 0
#define COMPARE 1



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

int fst3[12][2] = {{1,-1},{2,11},{3,8},
                  {4,-2},{5,-2},{6,-2},
                  {7,-1},{1,-1},{9,-2},
                  {10,-2},{7,-1},{-1,-1}};


List* pathTreeList; 
static int pathtreeCounter=0 ; //counter for the path-trees 


int main(int argc, char **argv){
  printf("Simulation starts...\n");
  
  Fst (*fst)[2] = fst2; // choose a Thompson fst

  char alphabet[ALPHABET_SIZE] = ALPHABET;
 
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


// copy a path-tree
  PathTree* pt2 =(PathTree*)malloc(sizeof(PathTree));
  copy_pathtree(initPt, pt2);

  
  // add_pathtree(pathTreeList,pt2);
  // pathtreeCounter++;

#if COMPARE
   printf("pathTree counter: %d \n Pathtrees: ", pathtreeCounter);
   print_list(pathTreeList); NEW_LINE;
#endif 

  List* leaves = (List*) malloc(sizeof(List));
  get_leaves(pt2,leaves);  
#if TEST
  printf("Pt2 Leaves: ");
  print_list(leaves); NEW_LINE;
#endif

  step(leaves, fst,'b');
  contract(pt2);
#if COMPARE
  print_pathtree(initPt); NEW_LINE;
  print_pathtree(pt2); NEW_LINE;
  printf("2nd: Compare initpt and pt2: %d\n",compare_pathtree(initPt, pt2));
#endif

  printf("is_contained pt2: %d\n", is_contained(pathTreeList,pt2));

//   int coverage = 0;
//   // char* output;
//   List* ptPointer = pathTreeList;

//   while(!coverage){ // check if the new-generated path-trees are coverd already
//   	int before = pathtreeCounter;

//     while(ptPointer->nodePt){ //visit all the path-trees
//   		PathTree* pt = ptPointer->nodePt;

//       for(int i=0; i<ALPHABET_SIZE; i++){
//         // create a new path-tree for extension on the symbol
//         PathTree* newPt =(PathTree*)malloc(sizeof(PathTree));
//         copy_pathtree(pt, newPt);

//         List* leaves = (List*) malloc(sizeof(List));
//         get_leaves(newPt, leaves);

// 		  	char symbol = alphabet[i];
//         step(leaves,fst,symbol);
//         contract(newPt);
// //		  prune(ptPointer); //?

//         // check if this newPt is already in the pathTreeList
//         if(!is_contained(pathTreeList,newPt)){ // a new path-tree
//           add_pathtree(pathTreeList,newPt);
//           pathtreeCounter++;
//         }
//  	 	  }
//       ptPointer = ptPointer->nextPt;
//     }
//     coverage = before == pathtreeCounter;
// 	}
}


