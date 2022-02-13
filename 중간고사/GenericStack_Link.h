//2017110853
#include <stdlib.h>

typedef struct t_StackNode {
    void* data;
    struct t_StackNode* next;
}Node;

typedef struct {
    int size;
    Node* head;
}Stack;

Stack* CreateStack() {
    Stack* pStack = malloc(sizeof(Stack));
    if (pStack == NULL) return 0;

    pStack->size = 0;
    pStack->head = NULL;

    return pStack;
}

int IsEmptyStack(Stack* stk) { return (stk->size) ? 0 : 1; }

void Push(Stack* stk, void* data) {
    Node* newN = malloc(sizeof(Node));

    newN->data = data;

    if (IsEmptyStack(stk)) {
        newN->next = NULL;
        stk->head = newN;
    }
    else {
        newN->next = stk->head;
        stk->head = newN;
    }
    stk->size++;
}

void* Pop(Stack* stk) {
    Node* del = malloc(sizeof(Node));
    void* poped;
    if (IsEmptyStack(stk)) {
        return 0;
    }
    else {
        del = stk->head;
        poped = del->data;
        stk->head = del->next;
        stk->size--;
    }
    return poped;
}

void* Top(Stack* stk) {
    if (IsEmptyStack(stk)) {
        return 0;
    }
    else {
        return stk->head->data;
    }
}

void DeleteStack(Stack* stk) {
    Node* pLoc = malloc(sizeof(Node));
    Node* pNxt = malloc(sizeof(Node));
    if (!IsEmptyStack(stk)) {
        for (pLoc = stk->head, pNxt = pLoc->next; stk->head != NULL; pLoc = pNxt, pNxt = pLoc->next) {
            if (pLoc == NULL || pNxt == NULL) return;
            stk->head = pNxt;
            free(pLoc->data); free(pLoc);
        }
    }
    free(stk);
}
