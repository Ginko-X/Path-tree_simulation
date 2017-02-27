#include <stdio.h>
#include <stdlib.h>
#include "path_tree.h"

#define Fst int


/* Generate the initial path tree for a given Thompson FST
 */

void path_tree_init(Fst (*fst)[2], PathTree* root){
	root->n = 0;
//		node->reg = ??
	closure_one(root,0,fst);
}
	

/* compute the set of epsilon-closure for the state 'st' in 'fst',
 */
void closure_one(TreeNode *node, int st, Fst (*fst)[2]){
	if( fst[st][0] == -1 || fst[st][1] < -1 ){ // final state or symbol transition state
		node->lchild = NULL;
		node->rchild = NULL;
	}
	else if(fst[st][1] == -1){ //epsilon transition state
		int newIndex = fst[st][0];
		node->n = newIndex;
		closure_one(node,newIndex,fst);
	}
	
	else{ // joint state
		TreeNode* lnode = (TreeNode*) malloc(sizeof(TreeNode));
		TreeNode* rnode = (TreeNode*) malloc(sizeof(TreeNode));
		int lst = fst[st][0];
		int rst = fst[st][1];
		lnode->n = lst;
		rnode->n = rst;
		closure_one(lnode,lst, fst);
		closure_one(rnode,rst, fst);
		node->lchild = lnode;
		node->rchild = rnode;
	}
}

//print out the path-tree states in a preorder traversal
void print_pathtree(TreeNode* root){
	if(root){
		printf("%d  ", root->n);
		if(root->lchild)
			print_pathtree(root->lchild);
		if(root->rchild)
			print_pathtree(root->rchild);
	}
}

/* Perform epsilon-closure on the 'pathTree'
 */
void closure(PathTree *pathTree, Fst (*fst)[2], int stateNum);


/* Compute the transition on the input 'symbol' 
 */
void step(PathTree *pathTree, Fst (*fst)[2], ICPair* leaves, char symbol);

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
ICPair* get_leaves(PathTree *pathTree);
