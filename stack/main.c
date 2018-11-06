//ADT_Stack
#include <stdio.h>
#include "ADT_stack.h"

int main(void){
	//Stack Creation
	STACK* stack_ptr;
	stack_ptr = create_stack();
	
	int i, k, m;
	
	// +->pushed 100
	i=100;
	if(!push(stack_ptr,&i)){
		printf("oops\n");
		return-1;
	}
	else{
		fill_space(stack_ptr->count);
		printf(" +->pushed: %d\n",i);
	}
	
	// +->pushed 200
	k=200;
	if(!push(stack_ptr,&k)){
		printf("oops\n");
		return-1;
	}
	else{
		fill_space(stack_ptr->count);
		printf(" +->pushed: %d\n",k);
	}
	
	// +->pushed 300
	m=300;
	if(!push(stack_ptr,&m)){
		printf("oops\n");
		return-1;
	}
	else{
		fill_space(stack_ptr->count);
		printf(" +->pushed: %d\n",m);
	}
	
	// pop 300
	if(stack_ptr->count!=0){
		fill_space(stack_ptr->count);
		printf(" <-popped: %d\n",*(int*)pop(stack_ptr));

	}
	else{
		printf("No more data.\n");
		return -1;
	}
	
	// push loop
	int idx;
	int data[10]={1,2,3,4,5,6,7,8,9,10};
	
	for(idx=0;idx<10;idx++){
		if(!push(stack_ptr,&(data[idx]))){
			printf("oops\n");
			return-1;
		}
		else{
			fill_space(stack_ptr->count);
			printf(" +->pushed: %d\n",data[idx]);
		}
	}
	
	// loop pop until empty
	while(stack_ptr->count !=0){
		if(stack_ptr->count!=0){
			fill_space(stack_ptr->count);
			printf(" <-popped: %d\n",*(int*)pop(stack_ptr));
	
		}
		else{
			printf("stack is empty.\n");
		}
	}
	//testing stack is really empty
	if(stack_ptr->count==0)
		printf("stack is empty");
	
	
}