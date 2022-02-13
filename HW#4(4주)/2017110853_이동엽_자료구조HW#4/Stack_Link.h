#include <stdio.h>
#include <stdlib.h>

typedef int Element;
typedef struct Nodes{
	Element data;
	struct Nodes* next;
}Node;

typedef struct{
	int size;
	Node* top;
}Stack;



Stack* CreateStack() {
	Stack* head = malloc(sizeof(Stack));
	Node* initial = malloc(sizeof(Node));
	if (head==NULL || initial == NULL) {
		return NULL;
	}

	head->size = 0;
	head->top = initial;

	initial->next = NULL;
	return head;
}

void Push(Stack* head, Element e) {
	Node *node = malloc(sizeof(Node));
	if (node == NULL) {
		return;
	}

	node->data = e;
	node->next = head->top;

	head->top = node;
	head->size++;
}

Element Top(Stack* head) {
	return (head->top)->data;
}

Element Pop(Stack* head) {
	Node* tp = head->top;
	Element e = tp->data;
	if (head->size > 0) {
		head->size--;
		head->top = tp->next;
		free(tp);
		return e;
	}
	else return 0;
}

void DestroyStack(Stack* head) {
	int s=head->size;
	for (int i = 0; i < s; i++) {
		Pop(head);
	}
	free(head);
}

int IsEmptyStack(Stack* head) {
	return (head->size==0) ? 1 : 0;
}