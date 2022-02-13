#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "Ad_List.h"
#include "Ad_Matrix.h"

void Process(void* data);

int main() {
	Graph* gra = CreateGraph(10, GCHAR);
	char fileN[20];
	char* v1 = (char*)malloc(sizeof(char));
	char* v2;
	FILE* in;

	printf("File name of a graph : ");
	scanf("%s", fileN);
	in = fopen(fileN, "r");

	if (!in) {
		printf("There is no file called \"%s\". Program terminates.", fileN);
		free(gra); exit(0);
	}

	fseek(in, 0, SEEK_END);
	if (!ftell(in)) {
		printf("There is nothing stored in file. Program terminates.\n");
		exit(0);
	}
	fseek(in, 0, SEEK_SET);

	fscanf(in, "%c\n", v1);
	InsertVertex(gra, (void*)v1);
	while (!feof(in)) {
		v1 = (char*)malloc(sizeof(char));
		v2 = (char*)malloc(sizeof(char));
		fscanf(in, "%c %c\n", v1, v2);
		if (!HasVertex(gra, v1)) {
			InsertVertex(gra, v1);
		}
		if (!HasVertex(gra, v2)) {
			InsertVertex(gra, v2);
		}
		AddEdge(gra, v1, v2);
	}
	fclose(in);
	printf("\n");
	Print_Graph(gra);
	printf("\nDepth First Traversal :");
	DepthFirstTraversal(gra, Process);
	printf("\nBreadth First Traversal :");
	BreadthFirstTraversal(gra, Process);
	printf("\n");
}

void Process(void* data) { printf(" %c", *(char*)data); }