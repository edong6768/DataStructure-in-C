#include <stdlib.h>
#include <string.h>
#include "Generic_Func.h"
#include "Tree_Queue.h"
#include "Array_Ops.h"

#define PRE 0
#define IN 1
#define POST 2
#define BF 3

typedef struct tree_node {
	void* data;
	struct tree_node** child;
	int (*compare)(void* data1, void* data2);
	void (*print)(void* data);
  	int type;
}TreeNode;

TreeNode* CreateTree(TreeNode* lft, void* data, TreeNode* rgt, int type) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (!newNode) return NULL;

	newNode->data = data;
    newNode->child=(TreeNode**)malloc(2*sizeof(TreeNode*));
    if (!newNode->child) {
        free(newNode);
        return NULL;
    } 
	newNode->child[0] = lft; newNode->child[1] = rgt;
	newNode->compare = (int (*)(void*, void*))Generic_Compare(type);
	newNode->print = (void (*)(void*))Generic_Print(type);
    newNode->type=type;
	return newNode;
}

TreeNode* LeftTree(TreeNode* root) { return root->child[0]; }
TreeNode* RightTree(TreeNode* root) { return root->child[1]; }

TreeNode* _leftMostNode(TreeNode* root, TreeNode** parent){
  if(!root->child[0]) return root;
  *parent=root;
  return _leftMostNode(root->child[0], parent);
}
TreeNode* _rightMostNode(TreeNode* root, TreeNode** parent){
  if(!root->child[1]) return root;
  *parent=root;
  return _rightMostNode(root->child[1], parent);
}

int IsEmpty(TreeNode* root) {
	if (!root->child[0] && !root->child[1] && !root->data) return 1;
	else return 0;
}
void* TreeData(TreeNode* node) { return node->data; }

TreeNode** DestroyNode(TreeNode* del){
  TreeNode** child=del->child;
  free(del->child);
  free(del);
  return child;
}
void DestroyTree(TreeNode* root) {
	if (!root) return;
    DestroyTree(root->child[0]);
    DestroyTree(root->child[1]);
	free(root);
}

TreeNode* _search_BST(TreeNode* root,TreeNode** parent,int* pChildIdx, void* data){
  if(!root) return NULL;
  if(root->compare(data,root->data)<0) {
    *parent=root;
    *pChildIdx=0;
    return _search_BST(root->child[0],parent,pChildIdx,data);
  }
  else if(root->compare(data,root->data)>0) {
    *parent=root;
    *pChildIdx=1;
    return _search_BST(root->child[1],parent,pChildIdx,data);
  }
  else return root;
}

int SearchBST(TreeNode* root, void* data){
  TreeNode* parent=NULL;
  int childIdx;
  return (_search_BST(root, &parent, &childIdx, data))?1:0;
}

TreeNode* InsertBST(TreeNode* root, void* data, int type) {
    TreeNode* newNode = CreateTree(NULL, data, NULL, type);
    TreeNode* parent=NULL;
    int childIdx;
    if (!root) {
        return newNode;
    }
    if(!_search_BST(root, &parent, &childIdx, data)) parent->child[childIdx]=newNode;
	return root;
}

void _breadth_first(TreeNode* root, void (*process)(void* data)) {
	TreeNode* temp = CreateTree(NULL, NULL, NULL, 0);
	Queue* nodeQue = CreateQueue();
	Enqueue(nodeQue, root);
	while (!IsEmptyQueue(nodeQue) || !temp) {
		temp = Dequeue(nodeQue);
		if (temp->data) process(temp->data);
		if (temp->child[0]) Enqueue(nodeQue, temp->child[0]);
		if (temp->child[1]) Enqueue(nodeQue, temp->child[1]);
	}
    DestroyTree(temp);
}
TreeNode* Traverse(TreeNode* root, int mode, void (*process)(void* data)) {
	if (!root || IsEmpty(root)) return NULL;
	switch (mode) {
	case PRE:
		if (root->data) process(root->data);
		if (root->child[0]) Traverse(root->child[0], mode, process);
		if (root->child[1]) Traverse(root->child[1], mode, process);
		break;
	case IN:
		if (root->child[0]) Traverse(root->child[0], mode, process);
		if (root->data) process(root->data);
		if (root->child[1]) Traverse(root->child[1], mode, process);
		break;
	case POST:
		if (root->child[0]) Traverse(root->child[0], mode, process);
		if (root->child[1]) Traverse(root->child[1], mode, process);
		if (root->data) process(root->data);
		break;
	case BF:		//breadth first
		_breadth_first(root, process);
		break;
	default:
		return root;
	}
	return NULL;
}

TreeNode* DeleteBST(TreeNode* root, void* data){
  TreeNode* parent=NULL;
  TreeNode* parent2=NULL;
  TreeNode *temp;
  int childIdx;
  TreeNode* del=_search_BST(root, &parent, &childIdx, data);

  if(!del) return NULL;

  if(!del->child[0]&&!del->child[1]) temp=NULL;
  else if(del->child[0]&&!del->child[1]) temp=root->child[0];
  else if(!del->child[0]&&del->child[1]) temp=root->child[1];
  else{
    temp=_rightMostNode(del->child[0], &parent2);
    parent2->child[1]=NULL;
    temp->child=DestroyNode(del);
  }

  if(!parent) root=temp;
  else parent->child[childIdx]=temp;

  if(del) DestroyNode(del);
  return root;
}

void PrintTree(TreeNode* root) {
    TreeNode* temp = CreateTree(NULL, NULL, NULL, 0);
    Queue* nodeQue = CreateQueue();
    Queue* realnodeQue = CreateQueue();
    int level_elm, i;

    Enqueue(nodeQue, root); Enqueue(realnodeQue, root);
    for (level_elm = 1, i = level_elm; !IsEmptyQueue(realnodeQue) || !temp; i--) {
        if (!i) {
            printf("\n");
            level_elm *= 2; i = level_elm;
        }
        temp = Dequeue(nodeQue);
        if (temp) {
            Dequeue(realnodeQue);

            root->print(temp->data);
            printf(" ");

            Enqueue(nodeQue, temp->child[0]);
            Enqueue(nodeQue, temp->child[1]);
            if (temp->child[0])Enqueue(realnodeQue, temp->child[0]);
            if (temp->child[1])Enqueue(realnodeQue, temp->child[1]);
        }
        else {
            printf("X ");
            Enqueue(nodeQue, NULL);
            Enqueue(nodeQue, NULL);
        }
    }
    for(;i>0;i--) {printf("X ");}
}


void** CreateHuffman(char* string){
	char** chars=malloc(strlen(string)*sizeof(char*));
	int* freq=calloc(strlen(string),sizeof(int));
	TreeNode** leaf, **inProcess, *root;
	int num_char=0, find;
	int *tempi, *pMin;
	void* temp;

	char** huffCode, *code;
    Queue* nodeQue = CreateQueue();
    Queue* realnodeQue = CreateQueue();

	char*** huff=malloc(sizeof(void*)*3);
	
	//string to char freq
	for(int i=0;i<strlen(string);i++){
		find=SearchArray((void*)chars,&(string[i]), num_char, _compare_char);
		if(find<0){
			chars[num_char]=malloc(sizeof(char));
			*chars[num_char]=string[i];
			freq[num_char++]++;
		}
		else freq[find]++;
	}

	//char sort by freq
	for(int i=0, min=1000, minIDX=i;i<num_char;i++, min=1000, minIDX=i){
		for(int j=i;j<num_char;j++){
			if(freq[j]<min||(freq[j]==min&&_compare_char((void*)chars[j],(void*)chars[minIDX])<0)){
				min=freq[j];
				minIDX=j;
			}
		}
		freq[minIDX]=freq[i];
		freq[i]=min;
		
		temp=(void*)chars[i];
		chars[i]=chars[minIDX];
		chars[minIDX]=(char*)temp;
	}

	//create array of trees with freq as data
	leaf=malloc(num_char*sizeof(TreeNode*));
	inProcess=malloc(num_char*sizeof(TreeNode*));
	for(int i=0;i<num_char;i++){
		leaf[i]=CreateTree(NULL,&freq[i],NULL,GINT);
		inProcess[i]=leaf[i];
	}

	//make huffman tree
	for(int i=num_char;i>1;i--){
		tempi=malloc(sizeof(int));
		*tempi=*(int*)inProcess[0]->data+*(int*)inProcess[1]->data;
		inProcess[0]=CreateTree(inProcess[0], tempi ,inProcess[1], GINT);
		DeleteArray((void**)inProcess, 1, i, _null_int);

		for(int j=0, min=1000, minIDX=j;j<i-1;j++, min=1000, minIDX=j){
			for(int k=j;k<i-1;k++){
				if(*(int*)inProcess[k]->data<min){
					min=*(int*)inProcess[k]->data;
					pMin=inProcess[k]->data;
					minIDX=k;
				}
			}
			temp=(void*)inProcess[j];
			inProcess[j]=inProcess[minIDX];
			inProcess[minIDX]=(TreeNode*)temp;
		}
	}
	root=inProcess[0];
	printf("\n");
	PrintTree(root);
	
	printf("\n");
	
	//generate huffman code
	huffCode=(char**)malloc(num_char*sizeof(char*));
	temp = (void*)CreateTree(NULL, NULL, NULL, 0);
    Enqueue(nodeQue, root); Enqueue(realnodeQue, root);
    for (int level_elm = 1, elm = level_elm, elm_temp, line=0; !IsEmptyQueue(realnodeQue) || !temp; elm--) {
        if (!elm) {
            level_elm *= 2; elm = level_elm; line++;
        }
        temp = (void*)Dequeue(nodeQue);
        if (temp) {
			Dequeue(realnodeQue);
            for(int idx=0;idx<num_char;idx++){
				if((TreeNode*)temp==leaf[idx]){	
					code=(char*)malloc(line*sizeof(char));
					elm_temp=level_elm-elm;
					
					for(int i=line-1;i>=0;i--){
						code[i]=(char)('0'+(elm_temp%2));
						elm_temp/=2;
					}
					huffCode[idx]=code;
					break;
				}
			}
            Enqueue(nodeQue, ((TreeNode*)temp)->child[0]);
            Enqueue(nodeQue, ((TreeNode*)temp)->child[1]);
            if (((TreeNode*)temp)->child[0])Enqueue(realnodeQue, ((TreeNode*)temp)->child[0]);
            if (((TreeNode*)temp)->child[1])Enqueue(realnodeQue, ((TreeNode*)temp)->child[1]);
        }
        else {
            Enqueue(nodeQue, NULL);
            Enqueue(nodeQue, NULL);
        }
    }

	//print Huffamn
	for(int i=0;i<num_char;i++){
		printf("%c %s\n", *chars[i], huffCode[i]);
	}
	printf("\n");
	
	for(int i=0;i<strlen(string);i++){
		find=SearchArray((void*)chars,&(string[i]), num_char, _compare_char);
		if(find>=0){
			printf("%s ",huffCode[find]);
		}
	}
	huff[0]=(void*)&num_char;
	huff[1]=(void*)chars;
	huff[2]=(void*)huffCode;
	return (void**)huff;
}

void EncodeHuff(char*** huff, char* string){
	int find;
	for(int i=0;i<strlen(string);i++){
		find=SearchArray((void**)(huff[1]),&(string[i]), *(int*)huff[0], _compare_char);
		if(find>=0){
			printf("%s ",((char**)(huff[2]))[find]);
		}
	}
}

void DecodeHuff(char*** huff, char* string){

}