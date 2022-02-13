#include <stdlib.h>
#include "Generic_Func.h"
#include "Tree_Queue.h"

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
    newNode->child=malloc(2*sizeof(TreeNode*));
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
/*void _insert_recur(TreeNode* root, TreeNode* add){
  if(root->compare(add->data,root->data)>0){
    if(!RightTree(root)) root->RightTree=add;
    else _insert_recur(root->RightTree,add);
  }
  else if(root->compare(add->data,root->data)<0){
    if(!LeftTree(root)) root->LeftTree=add;
    else _insert_recur(root->LeftTree,add);
  }
  return;
}*/

TreeNode* InsertBST(TreeNode* root, void* data, int type) {
    TreeNode* newNode = CreateTree(NULL, data, NULL, type);
    TreeNode* parent=NULL;
    int childIdx;
    if (!root) {
        return newNode;
    }
    if(!_search_BST(root, &parent, &childIdx, data)) parent->child[childIdx]=newNode;;
    //_insert_recur(root,newNode);
	return root;
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

    Enqueue(nodeQue, root); Enqueue(realnodeQue, root);
    for (int level_elm = 1, i = level_elm; !IsEmptyQueue(realnodeQue) || !temp; i--) {
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
}