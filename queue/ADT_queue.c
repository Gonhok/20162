#include "ADT_queue.h"

QUEUE*
create_queue() {
	QUEUE* newQ;
	newQ=(QUEUE*)malloc(sizeof(QUEUE));
	if(newQ){
		newQ->count=0;
		newQ->front=NULL;
		newQ->rear-NULL;
	}
	else
		return NULL;
	return newQ;
}

bool
enqueue(QUEUE* queue, void* in) {
	if(!queue)
		return false;
	QUEUE_NODE* newN;
	newN=(QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));
	newN->data_ptr=in;
	newN->next=NULL;
	if(!newN)
		return false;
	
	if(queue->count==0)
		queue->front=newN;
	else
		queue->rear->next=newN;
	queue->rear=newN;
	(queue->count)++;
	return true;
}

void* dequeue(QUEUE* queue) {
	if(queue->count==0)
		return NULL;
	QUEUE_NODE* tempN=queue->front;
	void* temp=queue->front->data_ptr;
	if(queue->count==1){
		queue->front=NULL;
		queue->rear=NULL;
	}
	else
		queue->front=queue->front->next;
	free(tempN);
	(queue->count)--;
	return temp;
}

void* queue_hook_front(QUEUE* queue) {
	if(queue->count==0)
		return NULL;
	else return queue->front->data_ptr;
}

void* queue_hook_rear(QUEUE* queue) {
	if(queue->count==0)
		return NULL;
	else return queue->rear->data_ptr;
}

void destroy_queue(QUEUE* queue) {
	if(queue!=NULL){
		int i=0;
		while(queue->count!=0){
			free(queue->front->data_ptr);
			dequeue(queue);
			printf("%d-th node is deleted\n",i++);
		}
	}
}