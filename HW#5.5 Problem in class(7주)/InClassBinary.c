#include <stdio.h>
#include "GenericStack_Link.h"

void Push_inverted(Stack** pstk, int dec);
char* Tochar(Stack** pstk);
int Bin_to_Dec(char* bin);
void ReadStack(Stack* stk);

int main(void) {
    Stack* binary = CreateStack();
    Stack* stk_Binary = CreateStack();
    char* bin;
    int mode, dec;

    while (1) {
        printf("Push(0), Pop(1), Exit(2) : ");
        scanf("%d", &mode);

        switch (mode) {
        case 0:
            printf("Push : ");
            scanf("%d", &dec);
            Push_inverted(&binary, dec);
            Push(stk_Binary, Tochar(&binary));
            break;
        case 1:
            if (IsEmptyStack(stk_Binary)) {
                printf("Stack is Empty!\n");
                break;
            }
            bin = (char*)Pop(stk_Binary);
            printf("Pop : %d (%s)\n", Bin_to_Dec(bin), bin);
            break;
        case 2:
            exit(0);
        default:
            printf("Select from given list!\n");
            break;
        }
        ReadStack(stk_Binary);
    }
}

void Push_inverted(Stack** pstk, int dec) {
    int* remainder = malloc(sizeof(int));
    if (dec == 0) return;
    *remainder = dec % 2;
    Push(*pstk, remainder);
    Push_inverted(pstk, dec / 2);
}

char* Tochar(Stack** stk) {
    char* binary = malloc(50 * sizeof(char));
    int i = 0;
    for (i = 0; !IsEmptyStack(*stk); i++) {
        binary[i] = ((*(int*)Pop(*stk)) == 0) ? '0' : '1';
    }
    binary[i] = '\0';
    return binary;
}

int Bin_to_Dec(char* bin) {
    int dec = 0;
    for (int i = 0; bin[i] != '\0'; i++) {
        dec += (bin[i] == '1') ? 1 : 0; dec *= 2;
    }
    return dec / 2;
}
