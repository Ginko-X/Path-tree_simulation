/* This file defines the basic operations about path trees. 
 */
#include "FST.h"

typedef struct TreeNode {
  int n; // state number, only meaningful for leaves node
  char *reg; // the bit string on the edge
  struct TreeNode *lchild; // 0-epsilon
  struct TreeNode *rchild; // 1-epsilon
} TreeNode;

typedef struct PathTree {
  TreeNode *root;
  TreeNode **notelist;
} PathTree;


/* Generate the initial path tree for a given Thompson FST
 */
PathTree* path_tree_init(Fst *fst);


/* compute the set of epsilon-closure for the state 'stateNum' in 'fst', 
 * result represented as a path tree
 */
PathTree* closure_one(PathTree pathTree, Fst *fst, int stateNum);


/* Perform epsilon-closure on the 'pathTree'
 */
PathTree* closure(PathTree pathTree, Fst *fst);


/* Compute the transition on the input 'symbol' 
 */
PathTree* step(PathTree *pathTree, Fst *fst, int stateNum, char symbol);


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
ICPair* leaves(PathTree *pathTree);











