#include <stdio.h>
#include <stdlib.h>

#include "ADT_stack.h"

STACK*
create_stack() {
	STACK* newStack = (STACK*)malloc(sizeof(STACK));
	newStack->count=0;
	newStack->top=NULL;
	return newStack;
}

bool
push(STACK* stack, void* in){
	STACK_NODE* newNode = (STACK_NODE*)malloc(sizeof(STACK_NODE));
	newNode->data_ptr=in;
	newNode->link=stack->top;
	stack->top=newNode;
	(stack->count)++;
	return true;
}

void*
pop(STACK* stack){
	if(stack->count==0)
		return NULL;
	else{
		STACK_NODE* tempNode = stack->top;
		void* tempData = stack->top->data_ptr;
		stack->top=stack->top->link;
		free(tempNode);
		(stack->count)--;
		return tempData;
	}
}

void fill_space(int size){
	for(int i=0;i<size;i++){
		printf(" ");
	}	
}