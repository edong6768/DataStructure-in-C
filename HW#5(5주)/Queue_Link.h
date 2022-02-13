#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* Element;

typedef struct Queue_node {
	Element data;
	struct Queue_node* next;
}Node;

typedef struct {
	int size;
	Node* front, * rear;
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
	Node* newN = malloc(sizeof(Node));
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
	Node* pNow;

	printf("The current status of Queue : (");
	pNow = que->front;
	for (int i = 0; i < que->size; i++) {
		printf("%s%d", pNow->data, i + 1);
		if (i < que->size - 1) printf(", ");
		pNow = pNow->next;
	}
	printf(")\n");
}