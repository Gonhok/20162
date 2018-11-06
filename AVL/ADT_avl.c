#include "ADT_avl.h"

#define LH +1
#define EH 0
#define RH -1

AVL_TREE* create_avl_tree() {
	AVL_TREE* tree = (AVL_TREE*)malloc(sizeof(AVL_TREE));
	if(!tree)
		return NULL;
	tree->count = 0;
	tree->root = NULL;
	return tree;
}

T_NODE* rotate_left(T_NODE* root){
	T_NODE* nRoot;
	nRoot = root->right;
	root->right = nRoot->left;
	nRoot->left = root;
	return nRoot;
}

T_NODE* rotate_right(T_NODE* root){
	T_NODE* nRoot;
	nRoot = root->left;
	root->left = nRoot->right;
	nRoot->right = root;
	return nRoot;
}

T_NODE* balance_left(T_NODE* root, bool* taller){
	T_NODE* left_tree;
	
	left_tree = root->left;
	switch(left_tree->balance){
		case LH:
		root->balance = EH;
		left_tree->balance = EH;
		root= rotate_right(root);
		*taller = false;
		break;
		case EH: exit(0);
		case RH:
		root->balance = EH;
		left_tree->balance = EH;
		left_tree=rotate_left(left_tree);
		root = rotate_right(root);
		*taller = false;
		break;
		}
	return root;
}

T_NODE* balance_right(T_NODE* root, bool* taller){
	T_NODE* right_tree;
	
	right_tree = root->right;
	switch(right_tree->balance){
		case LH:
		root->balance = EH;
		right_tree->balance = EH;
		right_tree=rotate_right(right_tree);
		root= rotate_left(root);
		*taller = false;
		break;
		case EH: exit(0);
		case RH:
		root->balance = EH;
		right_tree->balance = EH;
		root = rotate_left(root);
		*taller = false;
		break;
		}
	return root;
}

bool AVL_insert(AVL_TREE* tree, int data){
	T_NODE* newNode;
	bool taller;
	newNode = (T_NODE*)malloc(sizeof(T_NODE));
	if(!newNode) return false;
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode-> balance = EH;
	
	tree->root = insert_rotate(tree->root,newNode,&taller);
	
	(tree->count)++;
	return true;
}

T_NODE* insert_rotate(T_NODE* root, T_NODE* newNode, bool* taller){
	if(root==NULL){
		root=newNode;
		*taller = true;
		return root;
	}
	
	if((newNode->data)<(root->data)){
		root->left = insert_rotate(root->left,newNode,taller);
		if(*taller){
			switch(root->balance){
				case LH:
				root=balance_left(root, taller);
				break;
				case EH:
				root->balance=LH;
				break;
				case RH:
				root->balance=EH;
				*taller = false;
				break;
			}
		}
		return root;
	}
	else{
		root->right = insert_rotate(root->right,newNode,taller);
		if(*taller){
			switch(root->balance){
				case LH:
				root->balance=EH;
				*taller = false;
				break;
				case EH:
				root->balance=RH;
				break;
				case RH:
				root = balance_right(root,taller);
				break;
			}
		}
		return root;
	}
	return root;
}

T_NODE* delete_bst (T_NODE* root, int data, bool* success){
	if(!root){
		*success = false;
		return NULL;
	}
	if(data<root->data)
		root->left=delete_bst(root->left,data,success);
	else if(data>root->data)
		root->right=delete_bst(root->right,data,success);
	else{
		T_NODE* delNode = root;
		if(root->left==NULL){
			T_NODE* newRoot = root->right;
			free(delNode);
			*success = true;
			return newRoot;
		}
		else if(root->right==NULL){
			T_NODE* newRoot = root->left;
			free(delNode);
			*success = true;
			return newRoot;
		}
		else{
			T_NODE* search = root->left;
			while(search->right!=NULL)
				search=search->right;
			root->data = search->data;
			root->left = delete_bst(root->left,search->data,success);
		}
		
	}
	return root;
}


void traverse_preorder (T_NODE* root){
	printf("%d,",root->data);
	if(root->left)
		traverse_preorder(root->left);
	if(root->right)
		traverse_preorder(root->right);
}

void traverse_inorder (T_NODE* root){
	if(root->left)
		traverse_inorder(root->left);
	printf("%d,",root->data);
	if(root->right)
		traverse_inorder(root->right);
}

void traverse_postorder (T_NODE* root){
	if(root->left)
		traverse_postorder(root->left);
	if(root->right)
		traverse_postorder(root->right);
	printf("%d,",root->data);
}

void AVL_print (AVL_TREE* tree, int method){
	printf("AVL_TREE:\n");
	printf(" size : %d\n",tree->count);
	printf(" data : ");
	
	if(method==0)
		traverse_preorder(tree->root);
	else if(method==1)
		traverse_inorder(tree->root);
	else if(method==2)
		traverse_postorder(tree->root);
	else
		printf("type error");
	
	printf("\n");
}
