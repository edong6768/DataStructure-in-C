//2017110853
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* Element;

typedef struct Queue_node {
	Element data;
	struct Queue_node* next;
}QNode;

typedef struct {
	int size;
	QNode* front, * rear;
}Queue;

Queue* CreateQueue() {
	Queue* pQueue = malloc(sizeof(Queue));
	if (pQueue == NULL) {
		return 0;
	}

	pQueue->size = 0;
	pQueue->front = NULL;
	pQueue->rear = NULL;

	return pQueue;
}

int IsEmptyQueue(Queue* que) { return (que->size) ? 0 : 1; }

void Enqueue(Queue* que, Element e) {
	QNode* newN = malloc(sizeof(QNode));
	if (newN == NULL) { return; }
	newN->data = malloc(50 * sizeof(char));
	strcpy(newN->data, e);
	newN->next = NULL;

	if (que->size <= 0) {
		que->front = newN;
		que->rear = newN;
	}
	else {
		que->rear->next = newN;
		que->rear = newN;
	}
	que->size++;
}

Element Dequeue(Queue* que) {
	Element e;
	if (IsEmptyQueue(que)) {
		return 0;
	}
	else {
		e = que->front->data;
		que->front = que->front->next;
		que->size--;
		return e;
	}
}

void PrintAll(Queue* que) {
	QNode* pNow;

	printf("The current status of Queue : (");
	pNow = que->front;
	for (int i = 0; i < que->size; i++) {
		printf("%s%d", pNow->data, i + 1);
		if (i < que->size - 1) printf(", ");
		pNow = pNow->next;
	}
	printf(")\n");
}


void ReadQueue(Queue* que) {
    QNode* pLoc;
    printf("Queue List : ");
    for (pLoc = que->front; pLoc != NULL; pLoc = pLoc->next) printf("%s ", (char*)pLoc->data);
    printf("(%d)\n\n", que->size);
}
