#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Ad_Matrix3.h"

void Process(void* data) { printf(" %c", *(char*)data); }

int main() {
	Graph* gra = CreateGraph(10, GCHAR);
	char fileN[20];
	char* v1 = (char*)malloc(sizeof(char));
	char* v2;
	int weight;
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
		fscanf(in, "%c %c %d\n", v1, v2, &weight);
		if (!HasVertex(gra, v1)) {
			InsertVertex(gra, v1);
		}
		if (!HasVertex(gra, v2)) {
			InsertVertex(gra, v2);
		}
		AddEdge(gra, v1, v2, weight);
		AddEdge(gra, v2, v1, weight);
	}
	fclose(in);
	printf("\n");
	Print_Graph(gra);
	printf("\n");
	Minimim_Spanning_Tree_Print(gra);
	printf("\n");

	v1 = malloc(sizeof(char));
	*v1 = 'A';
	Shortest_Path(gra, v1);
}
