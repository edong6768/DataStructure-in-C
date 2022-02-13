#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;

typedef int Element;

typedef struct {
	Element *stack;		// array to store elements
  int size;		    // maximum size
  int top;			// stack top
} Stack;

Stack *CreateStack(int size)
{
	Stack *pStack = (Stack *)malloc(sizeof(Stack));
	if(pStack == NULL)
		return NULL;
	
	pStack->stack = (Element *)malloc(size * sizeof(Element));
	if(pStack->stack == NULL){
		free(pStack);
		return NULL;
	}

	pStack->size = size;
	pStack->top = -1;
	
	return pStack;
}

bool IsFullStack(Stack *pStack)
{
  	if(pStack->top == pStack->size - 1)
		  return true;
    else 
      return false;
}

void Push(Stack *pStack, Element item)
{
	// check if stack is full
	if(IsFullStack(pStack))
		return;

	pStack->stack[++pStack->top] = item;
}

bool IsEmptyStack(Stack *pStack)
{
  	if(pStack->top < 0)
		  return true;
    else 
      return false;
}

Element Pop(Stack *pStack)
{
	// check if stack is empty
	if(IsEmptyStack(pStack)) 
		return 0;

	return pStack->stack[pStack->top--];
}

Element Top(Stack *pStack)
{
	if(pStack->top < 0)		// stack is empty
		return 0;

	return pStack->stack[pStack->top];
}

void DestroyStack(Stack *pStack)
{
	if(pStack->size > 0)
		free(pStack->stack);	// dealloc memory
	free(pStack);
}
