#include <stdio.h>
#include "Queue_Link.h"

int main() {
	int mode;
	Element customer = malloc(50 * sizeof(Element));
	Queue* que = CreateQueue();

	do {
		printf("\nIn(0), out(1), exit(2) : ");
		scanf("%d", &mode);

		switch (mode) {
		case 0:
			printf("Customer : ");
			while (getchar() != '\n');
			scanf("%[^\n]s", customer);
			Enqueue(que, customer);
			break;
		case 1:
			if (IsEmptyQueue(que)) {
				printf("Queue is empty!\n");
				break;
			}
			printf("Customer dequeued : %s\n", Dequeue(que));
			break;
		case 2:
			exit(0);
		default:
			printf("Select from given list!\n");
			break;
		}

		while (getchar() != '\n');
		PrintAll(que);
	} while (1);
}

