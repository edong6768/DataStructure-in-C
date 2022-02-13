#include <string.h>
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
	printf("%s %s\n",(char*)data1, (char*)data2);
	return strcmp((char*)data1, (char*)data2);
}


//print func
void _print_int(void* data) {
	printf("%d",*(int*)data);
}

void _print_char(void* data) {
	printf("%c", *(char*)data);
}

void _print_str(void* data) {
	printf("%s ", (char*)data);
}

//generic
void* Generic_Print(int type) {
	switch (type) {
	case GINT:
		return _print_int;
	case GCHAR:
		return _print_char;
	case GSTR:
		return _print_str;
	default:
		return NULL;
	}
}

void* Generic_Compare(int type) {
	switch (type) {
	case GINT:
		return _compare_int;
	case GCHAR:
		return _compare_char;
	case GSTR:
		return _compare_str;
	default:
		return NULL;
	}
}