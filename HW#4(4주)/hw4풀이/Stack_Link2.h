#include <stdio.h>
#include <stdlib.h>

#define NoState -1
#define EndOfString 0
#define Operand 1
#define PLUS 2
#define MINUS 3
#define TIMES 4
#define MOD 5
#define Operator 6

typedef enum {false, true} bool;

typedef void* Element;

typedef struct tStackNode {
	Element data;
	struct tStackNode *next;
} StackNode;

typedef struct {
  int size;       // maximum size
	int count;
	StackNode *top;
} Stack;

Stack* CreateStack(int size)
// size is not used in linked list implementation
{
	Stack *pStack = (Stack *)malloc(sizeof(Stack));
	if(pStack == NULL)
		return NULL;
  pStack->size = size;
	pStack->count = 0;
	pStack->top = NULL;
	
	return pStack;
}

bool IsFullStack(Stack *pStack)
{
  	if(pStack->size == pStack->count)
		  return true;
    else 
      return false;
}

void Push(Stack *pStack, Element item)
{
  StackNode *pNewNode;

  if(IsFullStack(pStack))
		return;

	pNewNode = (StackNode *)malloc(sizeof(StackNode));
	if(pNewNode == NULL)
		return;

	pNewNode->data = item;
	pNewNode->next = pStack->top;
	pStack->top = pNewNode;
	pStack->count++;
}

bool IsEmptyStack(Stack *pStack)
{
  	if(pStack->top == NULL)
		  return true;
    else 
      return false;
}

Element Pop(Stack *pStack)
{
	if(IsEmptyStack(pStack)) 
		return 0;
	else {	
		Element item = pStack->top->data;
		StackNode *pOldTop = pStack->top;
		pStack->top = pOldTop->next;
		free(pOldTop);
		pStack->count--;
		return item;
	}
}

Element Top(Stack *pStack)
{
	if(pStack->top == NULL)		// stack is empty
		return 0;

	return pStack->top->data;
}

void DestroyStack(Stack *pStack)
{
  StackNode *bNode = NULL, *aNode = NULL ;

	if(pStack->count > 0)
  {
    aNode = pStack->top;
    while(aNode){
      bNode = aNode;
      aNode = bNode->next;
      free(bNode);
    }
  }
	free(pStack);
}