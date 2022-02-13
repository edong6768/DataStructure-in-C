//2017110853
#include <stdio.h>
#include "GenericStack_Link.h"
#include "Queue_Link.h"

void Push_inverted(Stack** pstk, int dec);
char* Tochar(Stack** pstk);
int Oct_to_Dec(char* bin);

int main(void) {
    Stack* octal = CreateStack();
    Queue* que_Octal = CreateQueue();
    char* bin;
    int mode, dec;

    while (1) {
        printf("Insert(0), Search(1), Delete(2), Exit(3) : ");
        scanf("%d", &mode);

        switch (mode) {
        case 0:
            printf("\nDecimal : ");
            scanf("%d", &dec);
            Push_inverted(&octal, dec);
            Enqueue(que_Octal, Tochar(&octal));
            break;
        case 1:
            printf("\nDecimal : ");
            scanf("%d", &dec);
            if(Oct_to_Dec(que_Octal->front->data)==dec){
              printf("\n%d [%s] is in Queue.\n", dec, que_Octal->front->data);
            }
            else if(Oct_to_Dec(que_Octal->rear->data)==dec){
              printf("\n%d [%s] is in Queue.\n", dec,que_Octal->rear->data);
            }
            else {
              Push_inverted(&octal, dec);
              printf("\n%d [%s] is not in Queue.\n", dec,Tochar(&octal));
            }
            break;
        case 2:
            if (IsEmptyQueue(que_Octal)) {
                printf("Stack is Empty!\n");
                break;
            }
            bin = (char*)Dequeue(que_Octal);
            printf("\n%d [%s] is dequeued.\n", Oct_to_Dec(bin), bin);
            break;
        case 3:
            exit(0);
        default:
            printf("Select from given list!\n");
            break;
        }
        ReadQueue(que_Octal);
    }
}

void Push_inverted(Stack** pstk, int dec) {
    int* remainder = malloc(sizeof(int));
    if (dec == 0) return;
    *remainder = dec % 8;
    Push(*pstk, remainder);
    Push_inverted(pstk, dec / 8);
}

char* Tochar(Stack** stk) {
    char* octal = malloc(50 * sizeof(char));
    int i = 0;
    for (i = 0; !IsEmptyStack(*stk); i++) {
        octal[i] = '0'+*(int*)Pop(*stk);
    }
    octal[i] = '\0';
    return octal;
}

int Oct_to_Dec(char* bin) {
    int oct = 0;
    for (int i = 0; bin[i] != '\0'; i++) {
        oct += (int)bin[i]-(int)'0'; oct*=8;
    }
    return oct / 8;
}


