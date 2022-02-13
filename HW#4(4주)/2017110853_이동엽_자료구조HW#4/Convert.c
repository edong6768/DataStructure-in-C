#include <stdio.h>
#include "Stack_Link.h"

int main(void) {
	Stack* a=CreateStack();
	Element num, div, remainder;
	
	printf("Enter a number: ");
	scanf("%d", &num);
	div = num;
	while (1) {
		remainder = div % 2;
		div /= 2;
		Push(a, remainder);
		if (div == 0) break;
	}
	printf("\nThe binary number of %d: ",num);
	while (IsEmptyStack(a) == 0) {
		printf("%d", Pop(a));
	}
	printf("\n");
	DestroyStack(a);
}