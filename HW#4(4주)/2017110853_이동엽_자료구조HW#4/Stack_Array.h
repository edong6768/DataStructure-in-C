#include <stdio.h>
#include <stdlib.h>

typedef int Element;
typedef struct{
	Element * stack;
	int size, top;
}Stack;

Stack* CreateStack(int size) {
	Stack* pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack == NULL) {
		return NULL;
	}

	pStack->stack = (Element*)malloc(size * sizeof(Element));
	if (pStack == NULL) {
		free(pStack);
		return NULL;
	}

	pStack->size = size;
	pStack->top = -1;

	return pStack;
}

void Push(Stack* pStack, Element e) {
	if (pStack->top < pStack->size-1) pStack->stack[++pStack->top] = e;
}

Element Top(Stack* pStack) {
	if (pStack->top > -1) return pStack->stack[pStack->top];
  	return 0;
}

Element Pop(Stack* pStack) {
	if (pStack->top > -1) return pStack->stack[pStack->top--];
	return 0;
}

void DestroyStack(Stack* pStack) {
	free(pStack);
}

int IsFullStack(Stack* pStack) {
	return (pStack->top + 1 == pStack->size) ? 1 : 0;
}

int IsEmptyStack(Stack* pStack) {
	return (pStack->top == -1) ? 1 : 0;
}