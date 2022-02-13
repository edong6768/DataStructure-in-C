#include <stdlib.h>

int SearchArray(void** array, void* key, int size, int (*compare)(void* d1, void* d2)) {
	int comp;
	for (int i = 0; i < size; i++) {
		comp = compare(array[i], key);
		if (comp == 0) return i;
		//else if (comp > 0) return -i - 1;
	}
	return -size - 1;
}
void InterChangeArray(void** array, int size, int idx1, int idx2) {
	void* temp;
	if (idx1 >= size || idx2 >= size)return;
	temp = array[idx1];
	array[idx1] = array[idx2];
	array[idx2] = temp;
	free(temp);
}

void AddArray(void** array, int size, int maxSize, int idx, void* data) {
	if (size == maxSize) return;
	if (size > idx) {
		for (int i = size - 1; i >= idx; i--) { array[i + 1] = array[i]; }
	}
	array[idx] = data;
}


void DeleteArray(void** array, int idx, int size, void (*initialize)(void* data)) {
	if (size == 0) return;
	for (int i = idx; i < size - 1; i++) {
		array[i] = array[i + 1];
	}
	initialize(array[size - 1]);
}

void DeleteArray_2D(void*** array, int idx, int size, void (*initialize)(void* data)) {
	if (size == 0) return;
	for (int i = 0; i < size - 1; i++) {
		for (int j = idx; j < size - 1; j++) {
			array[idx][i] = array[idx][i + 1];
			array[i][idx] = array[i + 1][idx];
		}
	}
	for (int i = 0; i < size; i++) {
		initialize(array[size - 1][i]);
		initialize(array[i][size - 1]);
	}
}
