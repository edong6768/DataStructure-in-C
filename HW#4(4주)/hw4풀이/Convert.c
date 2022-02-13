#include "Stack_Link.h"
//#include "Stack_Array.h"

int main(int argc, char *argv[])
{
	bool done = false;
  int element = 0;
	Stack *pStack = CreateStack(1000);

  do{
    printf("Enter a number: ");
    scanf(" %d", &element);
  } while(element<0);

  printf("\nThe binary number of %d: ", element);

	while(element>0){
		Push(pStack, element%2);
    element /=2;
	}

	while(!IsEmptyStack(pStack))
		printf("%d", Pop(pStack));
  printf("\n");
  
	DestroyStack(pStack);
	pStack = NULL;

	return 0;
}