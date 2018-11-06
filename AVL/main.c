// ADT List
#include <stdio.h>
#include <stdlib.h>
#include "ADT_avl.h"

#define PRE_ORDER 0
#define IN_ORDER 1
#define POST_ORDER 2

int main() {

	// Create
	AVL_TREE* tree = create_avl_tree();
	
	// Insertion Test
	for(int i =0; i<10; i++){
	if(!AVL_insert(tree,i+1))
		printf("tree insertion error\n");
	
	AVL_print(tree, PRE_ORDER);
	printf("\n\n");
	}
	
	
	
	return 0;
}