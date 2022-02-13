#include <stdio.h>
#include "Binary_Tree.h"

int main() {
	TreeNode* tree = NULL;
	char* string = (char*)malloc(50 * sizeof(char));

	printf("input a string: ");
	scanf("%s", string);
	for (int i = 0; string[i]; i++) { 
		tree=InsertCompleteTree(tree, &(string[i]), GCHAR);
	}


	printf("\nPre-order : "); Traverse(tree, PRE);
	printf("\n\nIN-order : "); Traverse(tree, IN);
	printf("\n\nPost-order : "); Traverse(tree, POST);
	printf("\n\nBreadth First : "); Traverse(tree, BF);
	printf("\n");
	
	DestroyTree(tree);
	free(string);
}