#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>


#include "path_tree.h"

#define A2I(x) (95-x)  // letters must be ACSII greater than 'a'
#define NEW_LINE  printf("\n")

#define FST 2

#define TEST 0

 // Simplified Thompson FST representation:
  // First column: the left choice, -1 means no outgoing edge,i.e. final state
  // Second column: the right choice or the transition symbol below: 
  // epsilon:-1; 
  // a:-2 
  // b:-3
  // c:-4,

//Peter Troelsen's Thesis Page 11
#define ALPHABET1 "abc"
#define ALPHABET_SIZE1  3
int fst1[9][2] = {{1,5},{2,-2},{3,-3},
  				   {0,4},{8,-1},{6,-2},
  				   {7,-4},{0,-1},{-1,-1}};


// Grathwohl's PhD Thesis Page 38
#define ALPHABET2 "ab"
#define ALPHABET_SIZE2  2
int fst2[17][2] = {{1,8},{2,-1},{3,5},
  					{4,-2},{2,-1},{6,-3},
  					{7,-1},{-1,-1},{9,-1},
  					{10,16},{11,14},{12,-2},
  					{13,-1},{9,-1},{15,-3},
  					{13,-1},{7,-1}};


// Grathwohl's PhD Thesis Page 32
int fst3[12][2] = {{1,-1},{2,11},{3,8},
                  {4,-2},{5,-2},{6,-2},
                  {7,-1},{1,-1},{9,-2},
                  {10,-2},{7,-1},{-1,-1}};


List* pathTreeList; 
static int pathtreeCounter=0 ; //counter for the path-trees 


int main(int argc, char **argv){

#if FST==1
  char alphabet[ALPHABET_SIZE1] = ALPHABET1;  
  char alphabetsize = ALPHABET_SIZE1;
  Fst (*fst)[2] = fst1; // choose a Thompson fst
#endif

#if FST==2
  char alphabet[ALPHABET_SIZE2] = ALPHABET2;  
  char alphabetsize = ALPHABET_SIZE2;
  Fst (*fst)[2] = fst2; // choose a Thompson fst
#endif

  // create the init path-tree
  PathTree* initPt =(PathTree*)malloc(sizeof(PathTree));
  path_tree_init(fst, initPt); 
  printf("The initial path-tree is: ");
  print_pathtree(initPt); NEW_LINE;

  // add the first path-tree to the list
  pathTreeList = (List*)malloc(sizeof(List));
  pathTreeList-> nodePt = NULL;
  pathTreeList-> nextPt = NULL;
  add_pathtree(pathTreeList, initPt); 
  pathtreeCounter++;


#if TEST // one step check
  PathTree* pt2 =(PathTree*)malloc(sizeof(PathTree));
  copy_pathtree(initPt, pt2);
  List* leaves = (List*) malloc(sizeof(List));
  get_leaves(pt2,leaves);  
  printf("Pt2 Leaves: "); print_leaves(leaves); NEW_LINE;

  int accepted = step(leaves, fst,'b');
  if(!accepted)
    printf("The symbol 'b' is not accepted.\n");
  else{
    contract(pt2);
    print_pathtree(initPt); NEW_LINE;
    print_pathtree(pt2); NEW_LINE;
    //printf("2nd: Compare initpt and pt2: %d\n",compare_pathtree(initPt, pt2));
//   printf("is_contained pt2: %d\n", is_contained(pathTreeList,pt2));//   printf("is_contained pt2: %d\n", is_contained(pathTreeList,pt2));
  }
#endif



  // char* output;
  List* ptPointer = pathTreeList;
  while(ptPointer){ //visit all the path-trees
  		PathTree* pt = ptPointer->nodePt;

      for(int i=0; i<alphabetsize; i++){
        // create a new path-tree for extension on the symbol
        PathTree* newPt =(PathTree*)malloc(sizeof(PathTree));
        copy_pathtree(pt, newPt);

        List* leaves = (List*) malloc(sizeof(List));
        get_leaves(newPt, leaves);

		  	char symbol = alphabet[i];
        int acceptablesymbol = step(leaves,fst,symbol);

        if(!acceptablesymbol){
          printf("The symbol '%c' is not acceptable.\n", symbol);
          continue;
        }
        else{
          contract(newPt);
  //		  prune(ptPointer); //?
          // check if this newPt is already in the pathTreeList
          if(!is_contained(pathTreeList,newPt)){ // a new path-tree
            printf("When read a '%c', generate a new path-tree:", symbol);
            print_pathtree(newPt); NEW_LINE;
            add_pathtree(pathTreeList,newPt);
            pathtreeCounter++;
          }
          else{
            printf("The transition on the symbol '%c' is into the path-tree: ", symbol);
            print_pathtree(newPt); NEW_LINE;
          }
        }
 	 	  }
     print_pathtreelist(pathTreeList);
     printf("Counter: %d\n", pathtreeCounter); NEW_LINE;
     ptPointer = ptPointer->nextPt;
    }
}


