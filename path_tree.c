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
		if(lnode && rnode){
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
		pr->lchild = NULL;
	else
		pr->rchild = NULL;
}


//'node': the leaf(pointer)
// st: the name of this leaf
void step_one(TreeNode* leaf, int st, char symbol, Fst (*fst)[2]){
	if(fst[st][1] == A2I(symbol)){
		TreeNode* newNode = (TreeNode*) malloc(sizeof(TreeNode));
		int newSt = fst[st][0];
		newNode->n = newSt;
		closure_one(newNode, newSt, fst);
		leaf->lchild = newNode;
		leaf->rchild = NULL;
	}
	else // kill this branch
		kill_one(leaf,st);
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
 * TODO: return the bits of the determinized stem if any
 */
void contract(PathTree *root){
	if(root){
		if(root->lchild && root->rchild){ // a joint node
			contract(root->lchild);
			contract(root->rchild);
		}
		else{ 
			if((root->lchild== NULL) && (root->rchild==NULL)) // a leaf
				return;
			else{ 
				TreeNode* p;
				if(root->lchild == NULL) //output bit 1					
					p = root->rchild;			
				else //output bit 0
					p = root->lchild;
				root->n = p->n;

				root->lchild = p->lchild;
				if(p->lchild)
					p->lchild->parent = root;

				root->rchild = p->rchild;
				if(p->rchild)
					p->rchild->parent = root;
				contract(root);
			}
		}
	}
}


// ??
void prune(PathTree *pathTree);

/* Check if the two path-trees are the same, two comparison conditions:
 * 1. all leaf states are the same
 * 2. all paths for each leaf are the same
 */
int compare_pathtree(PathTree* pt1, PathTree* pt2){
	List* leaves1 = (List*) malloc(sizeof(List));
	List* leaves2 = (List*) malloc(sizeof(List));
	get_leaves(pt1,leaves1);
	get_leaves(pt2,leaves2);

	List* p1 = leaves1;
	List* p2 = leaves2;

	while(p1 && p2){
		if((p1->nodePt->n == p2->nodePt->n) &&
			(path(pt1,p1->nodePt) == path(pt2,p2->nodePt))){
			p1 = p1->nextPt;
			p2 = p2->nextPt;
		}
		else{
			return -1;
		}
	}
	if(p1== NULL && p2 ==NULL)
		return 1; // equal
	else 
		return -1; // not equal
}

/* Compute the bit-path from the root to the leaf
 * The bits from left to right correspond to those in the path tree
 * from bottom to top 
 */
int path(PathTree *root, TreeNode *leaf){
	if(root ==leaf)
		return -1;  // only a root in the pathtree, no path

	unsigned int bits=0;
	TreeNode *p1, *p2;
	p1 = leaf;
	p2 = leaf;

	while(p1){
		p1 = p2->parent;		
		if(p1->lchild == p2)
			bits = bits<<1;
		else 
			bits = (bits<<1)+1;
		p2 = p1;	
		p1= p1->parent;
	}	

	return bits;
} 


void copy_treenode(TreeNode* src, TreeNode* dest){
	dest->n = src->n;
	dest->reg = src->reg;
	dest->lchild = NULL;
	dest->rchild = NULL;
	dest->parent = NULL;
}

/* Copy the pathtree 'src' into 'dest'
 */
void copy_pathtree(PathTree* src, PathTree* dest){
	if(src){
		copy_treenode(src, dest);
		if(src->lchild){
			TreeNode* p = (TreeNode*) malloc(sizeof(TreeNode));
			copy_pathtree(src->lchild,p);
			dest->lchild = p;
			p->parent = dest;
		}
		if(src->rchild){
			TreeNode* p = (TreeNode*) malloc(sizeof(TreeNode));			
			copy_pathtree(src->rchild,p);			
			dest->rchild = p;
			p->parent = dest;
		}
	}
}




