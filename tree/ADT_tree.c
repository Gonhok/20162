#include "ADT_tree.h"

BST_TREE* create_bst_tree() {
	BST_TREE* tree = (BST_TREE*)malloc(sizeof(BST_TREE));
	if(!tree)
		return NULL;
	tree->count = 0;
	tree->root = NULL;
	return tree;
}

T_NODE* find_smallest_node (T_NODE* root){
	if(!root)
		return NULL;
	if(root->left==NULL)
		return root;
	else
		find_smallest_node(root->left);
}

T_NODE* find_largest_node (T_NODE* root){
	if(!root)
		return NULL;
	if(root->right==NULL)
		return root;
	else
		find_largest_node(root->right);
}

T_NODE* search_bst (T_NODE* root, int key){
	if(!root)
		return NULL;
	if(key<root->data)
		search_bst(root->left,key);
	else if(key>root->data)
		search_bst(root->right,key);
	else
		return root;
}

T_NODE* add_bst (T_NODE* root, int data){
	if(!root){
		T_NODE* newNode = (T_NODE*)malloc(sizeof(T_NODE));
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->data = data;
		return newNode;
	}
	if(data<root->data){
		root->left=add_bst(root->left,data);
		return root;
	}
	else{
		root->right=add_bst(root->right,data);
		return root;
	}
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


bool BST_insert (BST_TREE* tree, int data){
	T_NODE* newRoot = add_bst(tree->root,data);
	if(!newRoot)
		return false;
	else{
		tree->root=newRoot;
		(tree->count)++;
		return true;
	}
}

bool BST_delete (BST_TREE* tree, int data){
	bool success;
	T_NODE* newRoot=delete_bst(tree->root,data,&success);
	if(success){
		tree->root=newRoot;
		(tree->count)--;
		if(tree->count==0)
			tree->root=NULL;
	}
	return success;
}

void BST_print (BST_TREE* tree, int method){
	printf("BST_TREE:\n");
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
