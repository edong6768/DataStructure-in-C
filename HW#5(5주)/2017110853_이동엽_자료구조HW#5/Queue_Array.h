#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* Element;

typedef struct {
	Element* data;
	int size, front, rear;
}Queue;

Queue* CreateQueue(int size) {
	Queue* pQueue = malloc(sizeof(Queue));
	if (pQueue == NULL) {
		return 0;
	}

	pQueue->data = malloc(size * sizeof(Element));
	if (pQueue->data == NULL) {
		free(pQueue);
		return 0;
	}
	pQueue->size = size;
	pQueue->front = -1;
	pQueue->rear = -1;

	return pQueue;
}

int IsFullQueue(Queue* que) { return ((que->rear + 1) % que->size == que->front) ? 1 : 0; }

int IsEmptyQue(Queue* que) { return (que->rear == que->front) ? 1 : 0; }

void Enqueue(Queue* que, Element e) {
	if (!IsFullQueue(que)) {
		if (que->front == -1) que->front++;
		que->rear = ++(que->rear) % que->size;
		que->data[que->rear] = malloc(50 * sizeof(char));
		strcpy(que->data[que->rear], e);
	}
}

Element Dequeue(Queue* que) {
	Element e = que->data[que->front];
	if (!IsEmptyQue(que)) {
		que->front = (++que->front) % que->size;
	}
	return e;
}

void PrintAll(Queue* que) {

	printf("The current status of Queue : (");
	for (int i = que->front, j = 1; i != (que->rear + 1) % que->size; i = (i + 1) % que->size, j++) {
		if (j != 1) printf(", ");
		printf("%s%d", que->data[i], j);
	}
	printf(")\n");
}