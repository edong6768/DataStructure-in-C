#include <string.h>

int Compare_int(void* data1, void* data2) {
	return (*(int*)data1) - (*(int*)data2);
}

int Compare_double(void* data1, void* data2) {
	return (int)(*(double*)data1 - *(double*)data2);
}

int Compare_string(void* data1, void* data2) {
	return strcmp(*(char**)data1, *(char**)data2);
}