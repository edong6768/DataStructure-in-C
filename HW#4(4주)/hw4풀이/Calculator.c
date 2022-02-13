#include "Stack_Link2.h"
//#include "Stack_Array2.h"

bool parseParen(Stack *pS, char *exp)
{
	int i = 0;

	while (*(exp + i) != '\0') {
		if (*(exp + i) == '(')
			Push(pS, exp + i);
		else {
			if (*(exp + i) == ')')
				if (Pop(pS) == NULL)
					return false;
		}
		i++;
	}
	if (IsEmptyStack(pS))
		return true;
	else
		return false;
}

bool isDigit(char *stest)
{
	if (*stest >= '0' && *stest <= '9')
		return true;
	else
		return false;
}

bool compareOP(char x, char y) {
	switch (x) {
	case '*':
	case '/':
	case '%':
		return true;
	case '+':
	case '-':
		switch (y) {
		case '*':
		case '/':
		case '%':
			return false;
		default:
			return true;
		}
		break;
	default:
		return false;
	}
}

bool InToPost(Stack *pS, char *src, char *dest)
{
	int i = 0, j = 0;
	char temp;
	int state = NoState;

	while (*(src + i) != '\0') {
		while (*(src + i) == ' ') {
			i++;
		}

		if (isDigit(src + i)) {
			if (state == Operand)
				return false;

			do {
				*(dest + j) = *(src + i);
				i++; j++;
			} while (isDigit(src + i));
			*(dest + j) = ' ';
			j++;

			state = Operand;
		}
		else if (*(src + i) == '(') {
			Push(pS, src + i);
			i++;
		}
		else if (*(src + i) == ')') {
			while ((temp = *((char *)Pop(pS))) != '(') {
				*(dest + j) = temp;
				j++;
				*(dest + j) = ' ';
				j++;
				i++;
			}
		}
		else {
			if (state == Operator)
				return false;
			// operator
			if (!IsEmptyStack(pS) && compareOP(*((char *)Top(pS)), *(src + i))) {
				*(dest + j) = *((char *)Pop(pS));
				j++;
				*(dest + j) = ' ';
				Push(pS, src + i);
				i++; j++;
			}
			else {
				Push(pS, src + i);
				i++;
			}

			state = Operator;
		}
	}

	while (!IsEmptyStack(pS)) {
		*(dest + j) = *((char *)Pop(pS));
		j++;
		*(dest + j) = ' ';
		j++;
	}
	*(dest + j) = '\0';

	return true;
}

int get_token(Element *symbol, char **Ex) {
	int i = 0;

	*symbol = *Ex;

	if (**Ex == '\0')
		return EndOfString;

	while (*(*Ex + i) != '\0' && *(*Ex + i) != ' ')
		i++;
	*(*Ex + i) = '\0';
	*Ex = *Ex + i + 1;

	if (isDigit((char *)(*symbol)))
		return Operand;
	switch (*((char *)(*symbol))) {
	case '+':
		return PLUS;
	case '-':
		return MINUS;
	case '*':
		return TIMES;
	case '%':
		return MOD;
	default:
		return Operator;
	}
}

int eval(Stack *pS, char *postEx)
{
	int token;
	int result;
	Element symbol = NULL;
	int op1, op2;
	char *pEx = postEx;
	char temp[100];

	token = get_token(&symbol, &pEx); 	    // Get next token (operator or operand)
	while (token != EndOfString) {
		if (token == Operand)
			Push(pS, symbol); 	      // Push operand
		else {
			op2 = atoi((char *)Pop(pS)); op1 = atoi((char *)Pop(pS)); 	// Pop two operands
			switch (token) {		  	// Calculate and Push the result
			case PLUS: result = op1 + op2; break;
			case MINUS: result = op1 - op2; break;
			case TIMES: result = op1 * op2; break;
			case MOD: result = op1 % op2; break;
			}
			sprintf(temp, "%d", result);
			Push(pS, temp);
		}
		token = get_token(&symbol, &pEx);
	}
	return atoi((char *)Pop(pS));			// Final result is stored in stack
}

int main()
{
	char input[100], postEx[100] = { '\0', };
	Stack *pStack = CreateStack(100);

	printf("Arithmetic Expression : ");
	scanf(" %[^\n]s", input);

	if (parseParen(pStack, input)) {
		if (!InToPost(pStack, input, postEx)) {
			printf("Error : Check the binary expression !\n");
			return 0;
		}
	}
	else {
		printf("Error : Check the pairs of Parenthesis!\n");
		return 0;
	}

	printf("Input : %s\nPost : %s\n", input, postEx);
	printf("Result : %d\n", eval(pStack, postEx));

	DestroyStack(pStack);
	pStack = NULL;

	return 0;
}