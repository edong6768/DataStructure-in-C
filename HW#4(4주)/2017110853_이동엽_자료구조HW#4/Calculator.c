#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Stack_Link.h"

int TestExpr(char* str);
char* Postfix(char* str);
int CalPost(char* strp);

int main(void) {
	char str[50];
	char* strpost;

	printf("Arithmetic Expression: ");
	scanf("%[^\n]s", str);

	switch (TestExpr(str)) {
	case 1:
		printf("Error: Check the pairs of Parenthesis! Program terminate");
		exit(0);
	case -1:
		printf("Error: Check the binary expression! Program terminate");
		exit(0);
	}

	printf("Input : %s\n", str);
	strpost = Postfix(str);
	printf("Post : %s\n", strpost);

	printf("Result : %d\n", CalPost(strpost));

}

int TestExpr(char* str) {
	int kets = 0, num_op = 0;
	for (int i = 0; i < strlen(str); i++) {
		if (isdigit(str[i]) == 0) {
			switch (str[i]) {
			case '+':case '-':	case '*': case '%':
				num_op--;
				break;
			case '(':
				kets++;
				break;
			case ')':
				kets--;
				break;
			default:
				break;
			}
		}
		else if (isdigit(str[i + 1]) == 0) num_op++;

		if (num_op < 0 || num_op>1) return -1;
	}
	if (kets != 0) return 1;
	return 0;
}

char* Postfix(char* str) {
	Stack* op = CreateStack();
	char* strpost = malloc(sizeof(str) * 2);
	int count = 0;

	for (int i = 0; i < strlen(str); i++) {
		if (isdigit(str[i]) == 0) {
			if (isdigit(strpost[count - 1]) != 0) strpost[count++] = ' ';
			switch (str[i]) {
			case '+':case '-':
				while (IsEmptyStack(op) == 0 && str[Top(op)] != '(') {
					strpost[count++] = str[Pop(op)];
					strpost[count++] = ' ';
				}
				Push(op, i);
				break;
			case '*': case '%':
				if (str[Top(op)] == '*' || str[Top(op)] == '%') {
					strpost[count++] = str[Pop(op)];
					strpost[count++] = ' ';
				}
				Push(op, i);
				break;
			case '(':
				Push(op, i);
				break;
			case ')':
				while (str[Top(op)] != '(') {
					strpost[count++] = str[Pop(op)];
					strpost[count++] = ' ';
				}
				Pop(op);
				break;
			default:
				break;
			}
		}
		else {
			strpost[count++] = str[i];
		}
	}
	if (isdigit(strpost[count - 1]) != 0) strpost[count++] = ' ';
	while (IsEmptyStack(op) == 0) {
		strpost[count++] = str[Pop(op)];
		strpost[count++] = ' ';
	}
	strpost[count++] = '\0';
	DestroyStack(op);

	return strpost;
}


int CalPost(char* strp) {
	Stack* cal = CreateStack();
	char* tok = strtok(strp, " ");
	char op;
	int n1, n2;

	while (tok != NULL) {
		if (isdigit(*tok) != 0) Push(cal, atoi(tok));
		else {
			n2 = Pop(cal); n1 = Pop(cal);
			op = tok[0];
			switch (op) {
			case '+':
				Push(cal, n1 + n2);
				break;
			case '-':
				Push(cal, n1 - n2);
				break;
			case '*':
				Push(cal, n1 * n2);
				break;
			case '%':
				Push(cal, n1 % n2);
				break;
			default:
				break;
			}
		}
		tok = strtok(NULL, " ");
	}
	n1 = Pop(cal);
	DestroyStack(cal);
	return n1;
}