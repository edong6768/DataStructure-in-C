#include <stdlib.h>

typedef struct{
	void** data;
	int size;
	int top;
}Stack;

Stack* CreateStack(int size) {
	Stack* newStack = (Stack*)malloc(sizeof(Stack));
	if (newStack == NULL) {
		return NULL;
	}

	newStack->data = (void*)malloc(size * sizeof(void*));
	if (newStack->data == NULL) {
		free(newStack->data);
		return NULL;
	}

	newStack->size = size;
	newStack->top = 0;

	return newStack;
}
int IsEmptyStack(Stack* stk) {return (stk->top == 0) ? 1 : 0;}
int IsFullStack(Stack* stk) { return(stk->size == stk->top) ? 1 : 0; }
void Push(Stack* stk, void* data) {
	if (IsFullStack(stk)) return;
	stk->data[stk->top++] = data;
}

void* Top(Stack* stk) {
	if (IsEmptyStack(stk)==1) return NULL;
	return stk->data[stk->top];
}

void* Pop(Stack* stk) {
	if (IsEmptyStack(stk)==1) return NULL;
	return stk->data[--stk->top];
}

void DeleteStack(Stack* stk) {
	if (IsEmptyStack(stk)==0) {
		for (int i = 0; i < stk->top; i++) {
			free(stk->data[i]);
		}
	}
	free(stk->data);
	free(stk);
}

void ReadStack(Stack* stk) {
	printf("STACK Stat : ");
	for (int i = 0; i < stk->top;i++) printf("%s ", (char*)stk->data[i]);
	printf("(%d)\n", stk->top);
}