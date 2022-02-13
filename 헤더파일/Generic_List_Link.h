#include <stdlib.h>

typedef struct list_node {
	void* data;
	struct list_node* link;
}Node;

typedef struct{
	Node* head;
	Node* pos;
	Node* rear;
	int (*compare)(void* data1, void* data2);
	int count;
}List;

List* CreateList(int (*compare)(void* data1, void* data2)) {
	List* newList = (List*)malloc(sizeof(List));
	if (newList == NULL) return NULL;
	newList->head = NULL; newList->rear=NULL; newList->pos = NULL;
	newList->compare = compare;newList->count = 0;
	
	return newList;
}

void _insertNode(List* list, Node* pPre, void* data) {
	Node* pNew = (Node*)malloc(sizeof(Node));
	if (pNew == NULL) return;
	pNew->data = data;
	if (pPre == list->rear) list->rear = pNew;

	if (pPre == NULL) {
		pNew->link = list->head;
		list->head = pNew;
	}
	else {
		pNew->link = pPre->link;
		pPre->link = pNew;
	}
	list->count++;
}

int _searchNode(List* list, Node** ppPre, Node** ppLoc, void* data) {
	for (*ppPre=NULL, *ppLoc = list->head; *ppLoc != NULL; *ppPre=*ppLoc, *ppLoc = (*ppLoc)->link) {
		if (list->compare((*ppLoc)->data, data) == 0) return 1;
		else if (list->compare((*ppLoc)->data, data) > 0) break;
	}
	return 0;
}

void _deleteNode(List* list, Node* pPre, Node* pLoc) {
  if(pPre==NULL) {
		list->head = pLoc->link;
		free(pLoc->data);
	}
	else {
		pPre->link = pLoc->link;
		free(pLoc->data);
	}
  if (pLoc == list->rear) list->rear = pPre;
  if(pLoc==list->pos) list->pos=pPre;

	free(pLoc);
	list->count--;
}

void AddList(List* list, void* data) {
	Node *pLoc = NULL, *pPre = NULL;
	if (!_searchNode(list, &pPre, &pLoc, data)) {
	  _insertNode(list, pPre, data);
	}
}

void RemoveList(List* list, void* data) {
	Node* pLoc = NULL, *pPre = NULL;
	if (_searchNode(list, &pPre, &pLoc, data)) {
		_deleteNode(list, pPre, pLoc);
	}
}

int SearchList(List* list, void* data) {
	Node* pLoc = NULL, * pPre = NULL;
	return _searchNode(list, &pLoc, &pPre, data);
}

int TraverseList(List* list, int fromWhere, void** pDataout) {
	if (fromWhere == 0) list->pos = list->head;
	else list->pos = list->pos->link;
	if (list->pos != NULL) {
		*pDataout = list->pos->data;
		return 1;
	}
	else {
		pDataout = NULL;
		return 0;
	}
}

void DestroyList(List* list) {
	for (Node *pDel = list->head; pDel != NULL; pDel = list->head) {
		_deleteNode(list, NULL, pDel);
	}
	free(list);
}


