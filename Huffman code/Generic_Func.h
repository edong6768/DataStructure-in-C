#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define GINT 1
#define GCHAR 2
#define GSTR 3


//compare func
int _compare_int(void* data1, void* data2) {
	return (*(int*)data1) - (*(int*)data2);
}

int _compare_char(void* data1, void* data2) {
	return (int)(*(char*)data1) - (int)(*(char*)data2);
}

int _compare_str(void* data1, void* data2) {
	return strcmp(*(char**)data1, *(char**)data2);
}

//copy data to new memory and return void*
void* _copy_int(void* data1) {
	int* i = (int*)malloc(sizeof(int));
	*i = *(int*)data1;
	return i;
}
void* _copy_char(void* data1) {
	char* i = (char*)malloc(sizeof(char));
	*i = *(char*)data1;
	return i;
}
/*void* _copy_str(void* data1) {
}*/


//print func
void _print_int(void* data) {
	printf("%d", *(int*)data);
}

void _print_char(void* data) {
	printf("%c", *(char*)data);
}

void _print_str(void* data) {
	printf("%s ", (char*)data);
}


//initializer
void _null_int(void* data) {
	data = calloc(1, sizeof(int));
}

void _null_char(void* data) {
	data = calloc(1, sizeof(char));
}

/*void _null_str(void** data) {
	(char*)data = "";
}*/


//generic
void* Generic_Print(int type) {
	switch (type) {
	case GINT:
		return (void*)_print_int;
	case GCHAR:
		return (void*)_print_char;
	case GSTR:
		return (void*)_print_str;
	default:
		return NULL;
	}
}

void* Generic_Compare(int type) {
	switch (type) {
	case GINT:
		return (void*)_compare_int;
	case GCHAR:
		return (void*)_compare_char;
	case GSTR:
		return (void*)_compare_str;
	default:
		return NULL;
	}
}

void* Null_data(int type) {
	switch (type) {
	case GINT:
		return (void*)_null_int;
	case GCHAR:
		return (void*)_null_char;
		/*case GSTR:
			temp = (void**)" ";*/
	default:
		return NULL;
	}
}