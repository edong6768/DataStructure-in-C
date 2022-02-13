#include <stdlib.h>
#include <stdio.h>
#include "Generic_Func.h"
#include "Graph_Queue_Link.h"
#include "Array_Ops.h"

typedef struct {
	int** adjacency;
	void** vertex;
	int* processed;
	int maxSize, size;
	int (*compare)(void* d1, void* d2);
	void (*printdata)(void* data);
	void (*initialize)(void* data);
}Graph;

Graph* CreateGraph(int maxSize, int mode) {
	Graph* newGraph = malloc(sizeof(Graph));
	if (!newGraph) return NULL;

	newGraph->adjacency = malloc(maxSize * sizeof(int*));
	if (!newGraph->adjacency) {
		free(newGraph);
		return NULL;
	}
	for (int i = 0; i < maxSize; i++) {
		newGraph->adjacency[i] = calloc(maxSize, sizeof(int));
		if (!newGraph->adjacency[i]) {
			free(newGraph->adjacency);
			free(newGraph);
			return NULL;
		}
	}
	newGraph->vertex = malloc(maxSize * sizeof(void*));
	if (!newGraph->vertex) {
		free(newGraph->adjacency);
		free(newGraph);
		return NULL;
	}

	newGraph->initialize = (void (*)(void* data))Null_data(mode);

	newGraph->processed = calloc(maxSize, sizeof(int));

	newGraph->maxSize = maxSize;
	newGraph->size = 0;
	newGraph->compare = (int (*)(void*, void*))Generic_Compare(mode);
	newGraph->printdata = (void (*)(void*))Generic_Print(mode);
	return newGraph;
}

void _print_abj(Graph* pGra) {	//print abjacent matrix
	for (int i = 0; i < pGra->size; i++) {
		for (int j = 0; j < pGra->size; j++) { printf("%d ", pGra->adjacency[i][j]); }
		printf("\n");
	}
}

int _searchVertex(Graph* pGra, void* data) {
	if (!pGra->size) return -1;
	return SearchArray(pGra->vertex, data, pGra->size, pGra->compare);
}
int HasVertex(Graph* pGra, void* data) {
	if (_searchVertex(pGra, data) >= 0) return 1;
	return 0;
}
void InsertVertex(Graph* pGra, void* data) {
	int idx = _searchVertex(pGra, data);
	int* empArrAbj = calloc(pGra->maxSize, sizeof(int));
	if (pGra->size == pGra->maxSize) return;
	if (idx < 0) {
		AddArray(pGra->vertex, pGra->size, pGra->maxSize, -idx - 1, data);	//add in order
		for (int i = 0; i < pGra->size; i++) {//add column of abjacent matrix
			for (int j = pGra->size - 1; j >= -idx - 1; j--) {
				pGra->adjacency[i][j + 1] = pGra->adjacency[i][j];
			}
			pGra->adjacency[i][-idx - 1] = 0;
		}
		AddArray((void**)pGra->adjacency, pGra->size, pGra->maxSize, -idx - 1, empArrAbj);	//add row of abjacent matrix
		pGra->size++;
	}
}
void DeleteVertex(Graph* pGra, void* data) {
	int del = _searchVertex(pGra, data);
	if (del == -1) return;
	DeleteArray_2D((void***)pGra->adjacency, del, pGra->size--, pGra->initialize);
}
void AddEdge(Graph* pGra, void* d1, void* d2) {
	int d1n = _searchVertex(pGra, d1);
	int d2n = _searchVertex(pGra, d2);
	if (d1n <= -1 || d2n <= -1) return;
	pGra->adjacency[d1n][d2n] = 1;
}
void DeleteEdge(Graph* pGra, void* d1, void* d2) {
	int d1n = _searchVertex(pGra, d1);
	int d2n = _searchVertex(pGra, d2);
	if (d1n <= -1 || d2n <= -1) return;
	pGra->adjacency[d1n][d2n] = 0;
}

void _df_recur(Graph* pGra, void (*process)(void* data), int idx) {
	process(pGra->vertex[idx]);
	pGra->processed[idx] = 1;
	for (int i = 0; i < pGra->size; i++) {
		if (pGra->adjacency[idx][i] && (!pGra->processed[i])) _df_recur(pGra, process, i);
	}
}

void _bf_recur(Graph* pGra, void (*process)(void* data), Queue** que, int idx) {
	int* abj;
	int end = 1;
	for (int i = 0; i < pGra->size; i++) {
		if (pGra->adjacency[idx][i] && (!pGra->processed[i])) {
			process(pGra->vertex[i]);
			pGra->processed[i] = 1;
			abj = malloc(sizeof(int));
			*abj = i;
			Enqueue(*que, abj);
		}
		end *= pGra->processed[i];
	}
	if (end) return;
	_bf_recur(pGra, process, que, *(int*)Dequeue(*que));
}

void DepthFirstTraversal(Graph* pGra, void (*process)(void* data)) {
	_df_recur(pGra, process, 0);
	for (int i = 0; i < pGra->size; i++) { pGra->processed[i] = 0; }
}
void BreadthFirstTraversal(Graph* pGra, void (*process)(void* data)) {
	Queue* que = CreateQueue();
	process(pGra->vertex[0]);
	pGra->processed[0] = 1;
	_bf_recur(pGra, process, &que, 0);
	DestroyQueue(que);
	for (int i = 0; i < pGra->size; i++) { pGra->processed[i] = 0; }
}

void Print_Graph(Graph* pGra) {
	printf("The graph is : \n");
	for (int i = 0; i < pGra->size; i++) {
		pGra->printdata(pGra->vertex[i]);
		printf(" : ");
		for (int j = 0; j < pGra->size; j++) {
			if (pGra->adjacency[i][j]) {
				pGra->printdata(pGra->vertex[j]);
				printf(" ");
			}
		}
		printf("\n");
	}
}