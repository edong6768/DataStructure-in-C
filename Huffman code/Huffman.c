#include <stdio.h>
#include "Huffman_Tree.h"

int main() {
	TreeNode* tree = NULL;
	char* string = (char*)malloc(50 * sizeof(char));
	char*** huff;

	printf("input a string: ");
	scanf("%s", string);
	huff=(char***)CreateHuffman(string);

	printf("\nUse : ");
	for(int i=0;i<*(int*)huff[0];i++){
		if(i>0)printf(" ,");
		printf("%c",*(((char**)(huff[1]))[i]));
	}
	printf("\nEnter Message : ");
	scanf("%s",string);

	EncodeHuff(huff,string);
	DecodeHuff(huff,string);
	
	DestroyTree(tree);
	free(string);
}