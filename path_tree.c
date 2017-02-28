#include <stdio.h>
#include <stdlib.h>
#include "path_tree.h"

#define Fst int
#define A2I(x) (95-x) 


/* Generate the initial path tree for a given Thompson FST
 */

void path_tree_init(Fst (*fst)[2], PathTree* root){
	root->n = 0;
    root->parent = NULL;
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
		lnode->parent = node;
		rnode->parent = node;
	}
}


/* Add a pathtree to the list */
void add_pathtree(List* list, PathTree* pt){
	if(list->nodePt==NULL){ // the init path-tree
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

// print the name of the path-trees/leaves in the list
void print_list(List* list){
	while(list){
		if(list->nodePt)
			printf("%d  ", list->nodePt->n);
		list = list->nextPt;
	}
}

/* Get the list of leaves (pointers)
 */
void get_leaves(PathTree *root, List* leaves){
	if(root){
		if((root->lchild==NULL) && (root->rchild==NULL))
			add_pathtree(leaves,root);
		else{ 
			if(root->lchild)
				get_leaves(root->lchild,leaves);
			if(root->rchild)
				get_leaves(root->rchild,leaves);
		}

	}
}

/* Perform epsilon-closure on the 'pathTree'
 */
void closure(PathTree *pathTree, Fst (*fst)[2], int stateNum);

void kill_one(TreeNode *node, int st){
	TreeNode* pr = node->parent;
	if(pr->lchild->n == st) // this 'node' is the lchild of its parent
		pr->lchild = pr->rchild;
	pr->rchild = NULL;
}

void kill(PathTree *pathTree, Fst (*fst)[2], ICPair* leaves, char symbol);


//'node': the leaf(pointer)
// st: the name of this leaf
void step_one(TreeNode* node, int st, char symbol, Fst (*fst)[2]){
	if(fst[st][1] == A2I(symbol)){
		TreeNode* newNode = (TreeNode*) malloc(sizeof(TreeNode));
		int newSt = fst[st][0];
		newNode->n = newSt;
		closure_one(newNode, newSt, fst);
		node->lchild = newNode;
		node->rchild = NULL;
	}
	else // kill this branch
		kill_one(node,st);
}


/* Compute the transition on the input 'symbol' 
 */
void step(List* leaves, Fst (*fst)[2], char symbol){
	while(leaves){
		if(leaves->nodePt){
			step_one(leaves->nodePt,leaves->nodePt->n, symbol, fst);
		}
		leaves = leaves->nextPt;
	}
}

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


