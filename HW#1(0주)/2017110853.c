#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char name[50];
    int age = 0;
    char sex;
    char* namep=malloc(sizeof(char)*50);
    int n=0;

    char stop[4] = "stop";

    while (1) {
        printf("\nProvide your personal information\nName: ");

        scanf("%s",name);
        if (strcmp(name, "stop")==0) break;
        scanf("%s", namep);

        printf("Age: ");
        scanf("%d", &age);

        printf("Sex (M/F): ");
        getchar();
        scanf("%c", &sex);

        printf("\nYour name is %s %s, your age is %d, your sex is %c\n", namep, name, age, sex);
    }
    return 0;
}