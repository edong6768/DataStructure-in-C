#include <stdio.h>
#include "Stack_Link.h"

int main(void) {
	Stack* a=CreateStack();
	Element e;
	int retVal=0;
	while (1) {
		printf("Enter a number: <Ctrl+d> to stop: ");
		retVal=scanf("%d", &e);
		if (retVal != 1) break;
		Push(a, e);
	}
	printf("The List of numbers reversed:\n");
	while (IsEmptyStack(a) == 0) {
		printf("%d\n", Pop(a));
	}
	DestroyStack(a);
}