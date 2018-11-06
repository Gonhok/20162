#include "ADT_llist.h"

LLIST* create_list(int (*cmp_func)(void* x,void* y),void (*print_func)(void* x)){
	LLIST* list = (LLIST*)malloc(sizeof(LLIST));
	if(!list)
		return NULL;
	list->front=NULL;
	list->rear=NULL;
	list->pos=NULL;
	list->count=0;
	list->cmp_func=cmp_func;
	list->print_func=print_func;
	
	return list;
}


bool add_node_at(LLIST* list, unsigned int index, void* data){
	if(!list)
		return false;
	if(index>list->count)
		return false;
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->data_ptr=data;
	newNode->next=NULL;
	
	if(list->count==0){
		list->front=newNode;
		list->rear=newNode;
		(list->count)++;
		return true;
	}
	
	if(index==0){
		newNode->next=list->front;
		list->front=newNode;
		(list->count)++;
		return true;
	}
	
	int pt=1;
	list->pos=list->front;
	
	while(pt!=index){
		list->pos=list->pos->next;
		pt++;
	}
	
	if(pt==list->count){
		list->pos->next=newNode;
		list->rear=newNode;
		(list->count)++;
		return true;
	}
	else{
		newNode->next=list->pos->next;
		list->pos->next=newNode;
		(list->count)++;
		return true;
	}
	
	return false;
}

bool del_node_at(LLIST* list, unsigned int index){
	if(!list)
		return false;
	if(index>=list->count)
		return false;
	if(list->count==0)
		return false;
	
	if(list->count==1){
		free(list->front);
		list->front=NULL;
		list->rear=NULL;
		(list->count)--;
		return true;
	}
	
	int pt=0;
	list->pos=list->front;
	NODE* pre=NULL;
	
	while(pt!=index){
		pre=list->pos;
		list->pos=list->pos->next;
		pt++;
	}
	
	if(index==0){
		list->front=list->pos->next;
		free(list->pos);
		list->pos=NULL;
		(list->count)--;
		return true;
	}
	else if(pt==(list->count-1)){
		pre->next=NULL;
		list->rear=pre;
		free(list->pos);
		list->pos=NULL;
		(list->count)--;
		return true;
	}
	else{
		pre->next=list->pos->next;
		free(list->pos);
		list->pos=NULL;
		(list->count)--;
		return true;
	}
	
	return false;
}

void* get_data_at(LLIST* list, unsigned int index){
	if(!list)
		return NULL;
	if(index>=list->count)
		return NULL;
	if(list->count==0)
		return NULL;
	
	int pt=0;
	list->pos=list->front;
	
	while(pt!=index){
		list->pos=list->pos->next;
		pt++;
	}
	
	return list->pos->data_ptr;
}

int find_data(LLIST* list, void* search_data){
	if(!list)
		return -1;
	
	int result;
	int pt=0;
	list->pos=list->front;
	
	while(pt<list->count){
		result=(list->cmp_func)(list->pos->data_ptr,search_data);
		
		if(result==0)
			return pt;
		
		list->pos=list->pos->next;
		pt++;
	}
	return -1;
}

LLIST* copy_list(LLIST* list){
	if(!list)
		return NULL;
	LLIST* newList=create_list(list->cmp_func,list->print_func);
	
	for(int i=0;i<list->count;i++){
		add_node_at(newList,i,get_data_at(list,i));
	}
	
	return newList;
}

void print_all(LLIST* list, NODE* from_front){
	if(!list)
		return;
	list->pos=from_front;
	while(list->pos!=NULL){
		(list->print_func)(list->pos->data_ptr);
		list->pos=list->pos->next;
	}
	
	return;
}
