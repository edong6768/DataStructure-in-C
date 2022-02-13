#include <stdio.h>
#include <string.h>

int main() {
    char name[50];
    int age = 0;
    char sex;
    char* namep;
    int n = 0;

    while (1) {
        printf("\nProvide your personal information\nName: ");

        scanf("%[^\n]",name);
        namep = strtok(name, " ");
        if (strcmp(namep, "stop") == 0) break;

        printf("Age: ");
        scanf("%d", &age);

        printf("Sex (M/F): ");
        getchar();
        scanf("%c", &sex);


        printf("\nYour name is %s %s, your age is %d, your sex is %c\n", strtok(NULL, " "), namep, age, sex);
        while (getchar() != '\n');
    }
    return 0;
}