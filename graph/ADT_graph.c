#include "ADT_llist.h"
#include "ADT_graph.h"

//utility function
int compare_vertex(void* x, void* y){
	VERTEX* left = (VERTEX*)x;
	VERTEX* right = (VERTEX*)y;
	
	return left->data - right->data;
}

void print_vertex(void* x){
	VERTEX* vertex = (VERTEX*)x;
	printf(" - vertex: %c\n",(char)(vertex->data));
}

int compare_arc(void* x, void* y){
	ARC* left = (ARC*)x;
	ARC* right = (ARC*)y;
	
	return left->to_vertex->data - right->to_vertex->data;
}

void print_arc(void* x){
	ARC* arc = (ARC*)x;
	
	printf(" -> : %c\n",(char)(arc->to_vertex->data));
}

//GRAPH ADT imlementation
GRAPH* create_graph(){
	GRAPH* graph = (GRAPH*)malloc(sizeof(GRAPH));
	if(!graph) return NULL;
	graph->vertex_list = create_list(compare_vertex,print_vertex);
	return graph;
}

bool g_insert_vertex(GRAPH* graph, int data){
	if(!graph) return false;
	
	VERTEX* newVertex = (VERTEX*)malloc(sizeof(VERTEX));
	if(!newVertex) return false;
	newVertex->data=data;
	newVertex->arc_list=create_list(compare_arc,print_arc);
	if(find_data(graph->vertex_list, newVertex)!=-1) return false;//check if already exists
	return add_node_at(graph->vertex_list,graph->vertex_list->count,newVertex);
}

bool g_delete_vertex(GRAPH* graph, int data){
	if(!graph) return false;
	VERTEX tmpVertex;
	tmpVertex.data=data;
	tmpVertex.arc_list=NULL;
	int loc=find_data(graph->vertex_list, &tmpVertex);
	if(loc==-1) return false;
	del_node_at(graph->vertex_list, loc);
	return true;
}

void print_vertex_all(GRAPH* graph){
	graph->vertex_list->pos=graph->vertex_list->front;
	for(int i=0;i<graph->vertex_list->count;i++){
		(*(graph->vertex_list->print_func))(graph->vertex_list->pos->data_ptr);
		graph->vertex_list->pos=graph->vertex_list->pos->next;
	}
}

bool g_insert_arc(GRAPH* graph, int from, int to){
	if(!graph) return false;
	VERTEX tmpVertex1;
	tmpVertex1.data=from;
	tmpVertex1.arc_list=NULL;
	
	int vertex_loc=find_data(graph->vertex_list,&tmpVertex1);
	if(vertex_loc==-1){
		printf("form_vertex %c: not found\n",(char)from);
		return false;
	}
	
	VERTEX* from_vertex=(VERTEX*)get_data_at(graph->vertex_list,vertex_loc);
	
	VERTEX tmpVertex2;
	tmpVertex2.data=to;
	tmpVertex2.arc_list=NULL;
	
	vertex_loc=find_data(graph->vertex_list,&tmpVertex2);
	if(vertex_loc==-1){
		printf("to_vertex %c: not found\n",(char)to);
		return false;
	}
	
	VERTEX* to_vertex=(VERTEX*)get_data_at(graph->vertex_list,vertex_loc);
	
	ARC* newArc = (ARC*)malloc(sizeof(ARC));
	newArc->to_vertex = to_vertex;
	
	return add_node_at(from_vertex->arc_list,from_vertex->arc_list->count,newArc);
}


void print_arc_all(GRAPH* graph) {
	VERTEX* vertexPt=NULL;
	graph->vertex_list->pos=graph->vertex_list->front;
	for(int i=0;i<graph->vertex_list->count;i++){
		vertexPt = (VERTEX*)get_data_at(graph->vertex_list,i);
		printf("vertex: %c\n", (char)vertexPt->data);
		vertexPt->arc_list->pos=vertexPt->arc_list->front;
		
		for(int j=0;j<vertexPt->arc_list->count;j++){
			printf("        ");
			(*(vertexPt->arc_list->print_func))(vertexPt->arc_list->pos->data_ptr);
			vertexPt->arc_list->pos=vertexPt->arc_list->pos->next;
		}
		graph->vertex_list->pos=graph->vertex_list->pos->next;
	}
}