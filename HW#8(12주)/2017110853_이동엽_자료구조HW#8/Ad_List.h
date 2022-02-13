#include <stdlib.h>
#include <stdio.h>
#include "Generic_Func.h"
#include "Graph_Queue_Link.h"


typedef struct vertex {
	struct vertex* link;
	void* data;
	int inDegree, outDegree;
	short processed;
	struct arc* pArcHead, * pArcRear;
}Vertex;

typedef struct arc {
	Vertex* destination;
	struct arc* nextArc;
}Arc;

typedef struct {
	int count;
	Vertex* head, * rear;
	int (*compare)(void* d1, void* d2);
	void (*printdata)(void* data);
}Graph;

Graph* CreateGraph(int mode) {
	Graph* newGraph = malloc(sizeof(Graph));
	if (!newGraph) return NULL;

	newGraph->head = NULL; newGraph->rear = NULL;
	newGraph->count = 0;
	newGraph->compare = (int (*)(void*, void*))Generic_Compare(mode);
	newGraph->printdata = (void (*)(void*))Generic_Print(mode);
	return newGraph;
}

void _insertVertex(Graph* pGra, Vertex* pPre, void* data) {
	Vertex* pNew = (Vertex*)malloc(sizeof(Vertex));
	if (!pNew) return;

	pNew->data = data;
	pNew->inDegree = 0; pNew->outDegree = 0;
	pNew->pArcHead = NULL; pNew->pArcRear = 0;
	pNew->processed = 0;
	if (pPre == pGra->rear) pGra->rear = pNew;

	if (!pPre) {
		pNew->link = pGra->head;
		pGra->head = pNew;
	}
	else {
		pNew->link = pPre->link;
		pPre->link = pNew;
	}
	pGra->count++;
}

int _searchVertex(Graph* pGra, Vertex** ppPre, Vertex** ppLoc, void* data) {
	for (*ppPre = NULL, *ppLoc = pGra->head; *ppLoc != NULL; *ppPre = *ppLoc, *ppLoc = (*ppLoc)->link) {
		if (pGra->compare((*ppLoc)->data, data) == 0) return 1;
		else if (pGra->compare((*ppLoc)->data, data) > 0) break;
	}
	return 0;
}

int _searchEdge(Graph* pGra, Arc** ppPre_Arc, Arc** ppLoc_Arc, Vertex* v1, Vertex* v2) {
	for (*ppPre_Arc = NULL, *ppLoc_Arc = v1->pArcHead; *ppLoc_Arc != NULL
		; *ppPre_Arc = *ppLoc_Arc, *ppLoc_Arc = (*ppLoc_Arc)->nextArc) {
		if ((*ppLoc_Arc)->destination == v2) return 1;
	}
	return 0;
}
void _deleteVertex(Graph* pGra, Vertex* pPre, Vertex* pLoc) {
	if (pPre == NULL) {
		pGra->head = pLoc->link;
		free(pLoc->data);
	}
	else {
		pPre->link = pLoc->link;
		free(pLoc->data);
	}
	if (pLoc == pGra->rear) pGra->rear = pPre;

	free(pLoc);
	pGra->count--;
}

void InsertVertex(Graph* pGra, void* data) {
	Vertex* pLoc = NULL, * pPre = NULL;
	if (!_searchVertex(pGra, &pPre, &pLoc, data)) _insertVertex(pGra, pPre, data);
}
void DeleteVertex(Graph* pGra, void* data) {
	Vertex* pLoc = NULL, * pPre = NULL;
	if (_searchVertex(pGra, &pPre, &pLoc, data)) _deleteVertex(pGra, pPre, pLoc);
}

void _addEdge(Graph* pGra, Vertex* v1, Vertex* v2) {
	Arc* newArc = malloc(sizeof(Arc));
	newArc->nextArc = NULL;
	newArc->destination = v2;

	if (!v1->pArcHead) {
		newArc->nextArc = v1->pArcHead;
		v1->pArcHead = newArc;
		v1->pArcRear = newArc;
	}
	else {
		v1->pArcRear->nextArc = newArc;
		v1->pArcRear = newArc;
	}
}
void _deleteEdge(Vertex* pVer, Arc* pPre_Arc, Arc* pLoc_Arc) {
	if (pPre_Arc == NULL) pVer->pArcHead = pLoc_Arc->nextArc;
	else pPre_Arc->nextArc = pLoc_Arc->nextArc;
	if (pLoc_Arc == pVer->pArcRear) pVer->pArcRear = pPre_Arc;
	free(pLoc_Arc);
}
void AddEdge(Graph* pGra, void* d1, void* d2) {
	Vertex* pLoc_v1 = NULL, * pLoc_v2 = NULL, * pPre = NULL;
	Arc* pLoc_Arc = NULL, * pPre_Arc = NULL;
	if (_searchVertex(pGra, &pPre, &pLoc_v1, d1) && _searchVertex(pGra, &pPre, &pLoc_v2, d2)) {
		if (!_searchEdge(pGra, &pPre_Arc, &pLoc_Arc, pLoc_v1, pLoc_v2)) {
			_addEdge(pGra, pLoc_v1, pLoc_v2);
			pLoc_v1->outDegree++; pLoc_v2->inDegree++;
		}
	}
}
void DeleteEdge(Graph* pGra, void* d1, void* d2) {
	Vertex* pLoc_v1 = NULL, * pLoc_v2 = NULL, * pPre = NULL;
	Arc* pLoc_Arc = NULL, * pPre_Arc = NULL;
	if (_searchVertex(pGra, &pPre, &pLoc_v1, d1) && _searchVertex(pGra, &pPre, &pLoc_v2, d2)) {
		if (!_searchEdge(pGra, &pPre_Arc, &pLoc_Arc, pLoc_v1, pLoc_v2)) {
			_deleteEdge(pLoc_v1, pPre_Arc, pLoc_Arc);
			pLoc_v1->outDegree--; pLoc_v2->inDegree--;
		}
	}
}

int HasVertex(Graph* pGra, void* data) {
	Vertex* pLoc = NULL, * pPre = NULL;
	return _searchVertex(pGra, &pPre, &pLoc, data);
}

void _reset_processed(Graph* pGra) {
	for (Vertex* pVer = pGra->head; pVer != NULL; pVer = pVer->link) { pVer->processed = 0; }
}
int _all_processed(Graph* pGra) {
	for (Vertex* pVer = pGra->head; pVer != NULL; pVer = pVer->link) {
		if (!pVer->processed) return 0;
	}
	return 1;
}

void _df_recur(Graph* pGra, Vertex* pVer, void (*process)(void* data)) {
	process(pVer->data);
	pVer->processed = 1;
	if (_all_processed(pGra)) return;
	for (Arc* pArc = pVer->pArcHead; pArc != NULL; pArc = pArc->nextArc) {
		if (!pArc->destination->processed) _df_recur(pGra, pArc->destination, process);
	}
}

void _bf_recur(Graph* pGra, Vertex* pVer, void (*process)(void* data), Queue** que) {
	if (!pVer->pArcHead) return;
	for (Arc* pArc = pVer->pArcHead; pArc != NULL; pArc = pArc->nextArc) {
		if (!pArc->destination->processed) {
			process(pArc->destination->data);
			pArc->destination->processed = 1;
			Enqueue(*que, pArc->destination);
		}
	}
	if (_all_processed(pGra)) return;
	_bf_recur(pGra, Dequeue(*que), process, que);
}

void DepthFirstTraversal(Graph* pGra, void (*process)(void* data)) {
	_df_recur(pGra, pGra->head, process);
	_reset_processed(pGra);
}
void BreadthFirstTraversal(Graph* pGra, void (*process)(void* data)) {
	Queue* que = CreateQueue();
	process(pGra->head->data);
	pGra->head->processed = 1;
	_bf_recur(pGra, pGra->head, process, &que);
	DestroyQueue(que);
	_reset_processed(pGra);
}

void Print_Graph(Graph* pGra) {
	printf("The graph is : \n");
	for (Vertex* Loc = pGra->head; Loc != NULL; Loc = Loc->link) {
		pGra->printdata(Loc->data);
		printf(" : ");
		for (Arc* Now = Loc->pArcHead; Now != NULL; Now = Now->nextArc) {
			pGra->printdata(Now->destination->data);
			printf(" ");
		}
		printf("\n");
	}
}