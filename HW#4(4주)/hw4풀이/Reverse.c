#include "Stack_Link.h"
//#include "Stack_Array.h"

int main()
{
	bool done = false;
	Stack *pStack = CreateStack(1000);

	while(!done){
		int element = 0;
		int retVal = 0;
		printf("Enter a number: <Ctrl+d> to stop: ");
		retVal = scanf(" %d", &element);
		if(retVal != 1)
		  break;
		Push(pStack, element);
	}

	printf("\nThe List of numbers reversed:\n");
	while(!IsEmptyStack(pStack))
		printf("%-3d\n", Pop(pStack));
  
	DestroyStack(pStack);
	pStack = NULL;

	return 0;
}