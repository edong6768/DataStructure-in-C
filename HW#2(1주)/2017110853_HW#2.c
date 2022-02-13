#include <stdio.h>
#include <string.h>

int main() {
    char strng[50];
    int num[2][10];
    char* token;
    int count_a = 0, total_b = 0, now=0;
    

    printf("Input : \n");
    
    for (int i = 0; i < 2; i++) {
        gets(strng);

        token = strtok(strng, " ");
        while (token != NULL && count_a < 10) {
            num[i][count_a] = atoi(token);
            if (count_a>0&&num[i][count_a] < num[i][count_a-1]) {
                printf("The input numbers are not in ascending order\n\n");
                exit(0);
            }
            count_a++; //total_b++;
            token = strtok(NULL, " ");
        }
        if (token != NULL || count_a<10) {
            printf("You sould input 10 numbers in each number series\n\n");
            exit(0);
        }
        count_a = 0;
    }
    /*if (total_b != 20) {
        printf("You sould input 20 numbers in total");
        exit(0);
    }*/

    count_a = 0; total_b = 0;
    now = (num[0][0] <= num[1][0]) ? num[0][0] : num[1][0];
    printf("\nOutput:\n%d",now);
    while(count_a<10 || total_b<10) {
        if (num[0][count_a] < num[1][total_b]) {
            if (num[0][count_a] > now) {
                now = num[0][count_a];
                printf(", %d", now);
            }
            count_a++;
        }
        if (num[0][count_a] >= num[1][total_b]) {
            if (num[1][total_b] > now) {
                now = num[1][total_b];
                printf(", %d", now);
            }
            total_b++;
        }
    }
    printf("\n\n");
    return 0;
}