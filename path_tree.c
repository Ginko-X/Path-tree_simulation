#include <stdio.h>
#include "path_tree.h"


/* Generate the initial path tree for a given Thompson FST
 */
void path_tree_init(Fst *fst, PathTree*);


/* compute the set of epsilon-closure for the state 'stateNum' in 'fst', 
 * result represented as a path tree
 */
PathTree* closure_one(PathTree pathTree, Fst *fst, int stateNum);


/* Perform epsilon-closure on the 'pathTree'
 */
void closure(PathTree *pathTree, Fst *fst, int stateNum);


/* Compute the transition on the input 'symbol' 
 */
void step(PathTree *pathTree, Fst *fst, ICPair* leaves, char symbol);

void kill(PathTree *pathTree, Fst *fst, ICPair* leaves, char symbol);

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
ICPair* get_leaves(PathTree *pathTree);

