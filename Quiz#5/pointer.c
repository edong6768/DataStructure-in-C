#include <stdio.h>

void get_in(int** in1, int** in2, int count);
int* add(int* in1, int* in2, int count);

int main(void) {
	int count, i;
	int* in1 = NULL, * in2 = NULL, * result = NULL;

	printf("# of input pairs : ");
	scanf("%d", &count);

	get_in(&in1, &in2, count);
	result = add(in1, in2, count);

	for (i = 0; i < count; i++) printf("%d + %d = %d\n", in1[i], in2[i], result[i]);

	free(in1); free(in2);
	return 0;
}

void get_in(int** ain1, int** ain2, int count) {
	
	*ain1 = (int*)malloc(count * sizeof(int));
	*ain2 = (int*)malloc(count * sizeof(int));

	for (int i = 0; i < count; i++) {
		printf("in1 in2 : ");
		scanf("%d %d", *ain1+i, *ain2+i);
	}
}

int* add(int* in1, int* in2, int count) {
	int* temp = (int*)malloc(count * sizeof(int));
	for (int i = 0; i < count; i++) {
		temp[i] = in1[i] + in2[i];
	}
	return temp;
}