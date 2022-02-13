#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
	char name[20];
	int age;
	int score[3];

} Student;

void sorter(Student* stds, int sortby, int line);
void printer(Student* stds, int sortby, int i);

int main(){
	int menu, sortby, fileE=0;
	char fileN[20], isn;
	int line;
	FILE* in;
	Student* stds;
	Student temp;


	while (1) {
		printf("1) Insert\n2) Sort\n3) Quit\nSelect a menu : ");
		scanf("%d", &menu);

		switch (menu) {
		case 1:
			printf("\nFile name : ");
			scanf("%s", fileN);
			in = fopen(fileN, "r");
			if (in == NULL) {
				printf("There is no file called \"%s\". Program terminates.\n", fileN);
				exit(0);
			}
			fileE = 1;

			line = 1;
			while (feof(in) == 0) {		//count lines
				fscanf(in, "%c", &isn);
				if (isn == '\n') line++;
			}

			if (!ftell(in)) {		//empty file detection
				printf("There is nothing stored in file. Program terminates.\n");
				exit(0);
			}

			stds = malloc(sizeof(Student) * line);
			fseek(in, 0, SEEK_SET);
			for (int i = 0; i < line; i++) {
				fscanf(in, "%s %d %d %d %d", stds[i].name, &stds[i].age, &stds[i].score[0],
					&stds[i].score[1], &stds[i].score[2]);

				if (stds[i].age < 0) {		//negative age detection
					printf("Result: The age cannot be a negative number. Program terminates.\n");
					exit(0);
				}
				for (int j = 0; j < 3; j++) {		//wrong grade range detection
					if (stds[i].score[j] < 0 || stds[i].score[j]>100) {
						printf("Result: The grades must be between 0~100. Program terminates.\n");
						exit(0);
					}
				}
			}
			fclose(in);

			sorter(stds, 1, line);
			for (int i = 0; i < line; i++) {
				printer(stds, 1, i);
			}
			break;
		case 2:
			if (fileE==0) {
				printf("Result : There is no data to be sorted. Program terminates.\n");
				exit(0);
			}
			printf("\n1) Name\n2) Age\n3) Math\n4) English\n5) History\nChoose the field to sort by : ");
			scanf("%d", &sortby);

			sorter(stds, sortby, line);
			for (int i = 0; i < line; i++) {
				printer(stds, sortby, i);
			}
			break;
		case 3:
			exit(0);
			break;
		default:
			printf("invalid Entry! Select from above.\n\n\n");
			break;

		}
		while (getchar() != '\n');
		printf("\n\n");
	}
}

void sorter(Student* stds, int sortby, int line) {
	Student temp;
	int min;

	switch (sortby) {
	case 1:
		for (int i = 0; i < line - 1; i++) {
			min = i;
			for (int j = i + 1; j < line; j++) {
				if (strcmp(stds[i].name, stds[j].name) > 0) min = j;
			}
			if (i != min) {
				temp = stds[i];
				stds[i] = stds[min];
				stds[min] = temp;
			}
		}
		break;
	case 2:
		for (int i = 0; i < line; i++) {
			min = i;
			for (int j = i + 1; j < line; j++) {
				if (stds[i].age > stds[j].age) min = j;
			}
			if (i != min) {
				temp = stds[i];
				stds[i] = stds[min];
				stds[min] = temp;
			}
		}
		break;
	case 3:case 4:case 5:
		for (int i = 0; i < line; i++) {
			min = i;
			for (int j = i + 1; j < line; j++) {
				if (stds[i].score[sortby - 3] > stds[j].score[sortby - 3]) min = j;
			}
			if (i != min) {
				temp = stds[i];
				stds[i] = stds[min];
				stds[min] = temp;
			}
		}
		break;
	default:
		break;
	}
}
void printer(Student* stds, int sortby, int i) {
	switch (sortby) {
	case 1:
		if (i == 0) printf("\nResult:\nNo   Name Age English Math History\n");
		printf("%-2d %6s %3d %7d %4d %7d\n", i + 1, stds[i].name, stds[i].age, stds[i].score[0],
			stds[i].score[1], stds[i].score[2]);
		break;
	case 2:
		if (i == 0) printf("\nResult:\nNo Age   Name English Math History\n");
		printf("%-2d %3d %6s %7d %4d %7d\n", i + 1, stds[i].age, stds[i].name, stds[i].score[0],
			stds[i].score[1], stds[i].score[2]);
		break;
	case 3:
		if (i == 0) printf("\nResult:\nNo English   Name Age Math History\n");
		printf("%-2d %7d %6s %3d %4d %7d\n", i + 1, stds[i].score[0], stds[i].name, stds[i].age,
			stds[i].score[1], stds[i].score[2]);
		break;
	case 4:
		if (i == 0) printf("\nResult:\nNo Math   Name Age English History\n");
		printf("%-2d %4d %6s %3d %7d %7d\n", i + 1, stds[i].score[1], stds[i].name, stds[i].age,
			stds[i].score[0], stds[i].score[2]);
		break;
	case 5:
		if (i == 0) printf("\nResult:\nNo History   Name Age English Math\n");
		printf("%-2d %7d %6s %3d %7d %4d\n", i + 1, stds[i].score[2], stds[i].name, stds[i].age,
			stds[i].score[0], stds[i].score[1]);
		break;
	default:
		break;
	}
}