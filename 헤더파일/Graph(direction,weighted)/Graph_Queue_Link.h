#include <stdlib.h>

typedef struct Queue_node {
	void* data;
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

void Enqueue(Queue* que, void* e) {
	QNode* newN = malloc(sizeof(QNode));
	if (newN == NULL) { return; }
	newN->data = e;
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

void* Dequeue(Queue* que) {
	void* e;
	QNode* del;
	if (IsEmptyQueue(que)) {
		return 0;
	}
	else {
		e = que->front->data;
		del = que->front;
		que->front = que->front->next;
		que->size--;
		free(del);
		return e;
	}
}

void DestroyQueue(Queue* que) {
	while (que->size) {
		Dequeue(que);
	}
	free(que);
}
