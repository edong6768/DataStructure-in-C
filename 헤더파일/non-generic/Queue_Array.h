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
	pQueue->front = size-1;
	pQueue->rear = size-1;

	return pQueue;
}

int IsFullQueue(Queue* que) { return ((que->rear + 1) % que->size == que->front) ? 1 : 0; }

int IsEmptyQueue(Queue* que) { return (que->rear == que->front) ? 1 : 0; }

void Enqueue(Queue* que, Element e) {
	if (!IsFullQueue(que)) {
		que->rear = ++(que->rear) % que->size;
    printf("%d\n",que->rear);
		que->data[que->rear] = malloc(50 * sizeof(char));
		strcpy(que->data[que->rear], e);
	}
}

Element Dequeue(Queue* que) {
	Element e = que->data[que->front+1];
	if (!IsEmptyQueue(que)) {
		que->front = (++que->front) % que->size;
    return e;
	}
	return 0;
}

void PrintAll(Queue* que) {

	printf("The current status of Queue : (");
	for (int j = 1; (que->front+j)%que->size != que->rear+1; j++) {
		if (j != 1) printf(", ");
		printf("%s%d", que->data[(que->front+j)%que->size], j);
	}
	printf(")\n");
}