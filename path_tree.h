/* This file defines the basic operations about path trees. 
 */
//#include "FST.h"
#include "Utils.h"
#define Fst int

typedef struct TreeNode {
  int n; // state number, only meaningful for leaves node
  char *reg; // the bit string on the edge
  struct TreeNode *lchild; // 0-epsilon
  struct TreeNode *rchild; // 1-epsilon
  struct TreeNode *parent;
} TreeNode;

typedef TreeNode PathTree;

typedef struct List List;
struct List{
	PathTree *nodePt; // the init path-tree
	List *nextPt;
};


void add_pathtree(List* list, PathTree* pt);


/* Generate the initial path tree for a given Thompson FST
 */
void path_tree_init(Fst (*fst)[2], PathTree*);

void print_pathtree(TreeNode* root);


/* compute the set of epsilon-closure for the state 'stateNum' in 'fst', 
 * result represented as a path tree
 */
void closure_one(TreeNode *node, int, Fst (*fst)[2]);


/* Perform epsilon-closure on the 'pathTree'
 */
void closure(PathTree *pathTree, Fst (*fst)[2], int stateNum);


/* Compute the transition on the input 'symbol' 
 */
//void step(PathTree *pathTree, Fst (*fst)[2], char symbol);
void step(List* leaves, Fst (*fst)[2], char symbol);

void kill(PathTree *pathTree, Fst (*fst)[2], ICPair* leaves, char symbol);

/* Contract the path-tree by merging all the determinized states
 * return the bits of the determinized stem if any
 */
char* contract(PathTree *pathTree);

// ??
void prune(PathTree *pathTree);


/*************** Basic operations for Path Tree  ***********************/
// Reference: Grathwolh's PhD Thesis Page 99 

/* Get the root node of a path tree 
 */
TreeNode* get_root(PathTree *pathTree);

/* Compute the path from the root to the leaf node, which is represented as
 * a string of bits
 */
char* path(PathTree *pathTree, TreeNode *leaf, TreeNode *root); 


/* Get the list of leaves, which is represented as:
 * a list of ICPairs
 */
//ICPair* get_leaves(PathTree *pathTree);











