#include <stdlib.h>
#include "Generic_Func.h"
#include "Tree_Queue.h"

#define PRE 0
#define IN 1
#define POST 2
#define BF 3

typedef struct tree_node {
	void* data;
	struct tree_node* lft, * rgt;
	int (*compare)(void* data1, void* data2);
	void (*print)(void* data);
}TreeNode;

TreeNode* CreateTree(TreeNode* lft, void* data, TreeNode* rgt, int type) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (!newNode) return NULL;

	newNode->data = data;
	newNode->lft = lft; newNode->rgt = rgt;
	newNode->compare = (int (*)(void*, void*))Generic_Compare(type);
	newNode->print = (void (*)(void*))Generic_Print(type);
	return newNode;
}

TreeNode* LeftTree(TreeNode* root) { return root->lft; }
TreeNode* RightTree(TreeNode* root) { return root->rgt; }
int IsEmpty(TreeNode* root) {
	if (!root->lft && !root->rgt && !root->data) return 1;
	else return 0;
}
void* TreeData(TreeNode* node) { return node->data; }

void DestroyTree(TreeNode* root) {
	if (!root) return;
	DestroyTree(root->lft);
	DestroyTree(root->rgt);
	free(root);
}
void _breadth_first(TreeNode* root) {
	TreeNode* temp = CreateTree(NULL, NULL, NULL, 0);
	Queue* nodeQue = CreateQueue();
	Enqueue(nodeQue, root);
	while (!IsEmptyQueue(nodeQue) || !temp) {
		temp = Dequeue(nodeQue);
		if (temp->data) temp->print(temp->data);
		if (temp->lft) Enqueue(nodeQue, temp->lft);
		if (temp->rgt) Enqueue(nodeQue, temp->rgt);
	}
	DestroyTree(temp);
}
TreeNode* Traverse(TreeNode* root, int mode) {
	if (!root || IsEmpty(root)) return NULL;
	switch (mode) {
	case PRE:
		if (root->data) root->print(root->data);
		if (root->lft) Traverse(root->lft, mode);
		if (root->rgt) Traverse(root->rgt, mode);
		break;
	case IN:
		if (root->lft) Traverse(root->lft, mode);
		if (root->data) root->print(root->data);
		if (root->rgt) Traverse(root->rgt, mode);
		break;
	case POST:
		if (root->lft) Traverse(root->lft, mode);
		if (root->rgt) Traverse(root->rgt, mode);
		if (root->data) root->print(root->data);
		break;
	case BF:		//breadth first
		_breadth_first(root);
		break;
	default:
		return root;
	}
	return NULL;
}

TreeNode* InsertCompleteTree(TreeNode* root, void* data, int mode) {
	TreeNode* newNode = CreateTree(NULL, data, NULL, mode);
	TreeNode* temp = CreateTree(NULL, NULL, NULL, mode);
	Queue* nodeQue = CreateQueue();

	if (!root) {
		return newNode;
	}
	Enqueue(nodeQue, root);

	while (1) {
		temp = Dequeue(nodeQue);
		if (!temp->lft || !temp->rgt) break;
		Enqueue(nodeQue, temp->lft);
		Enqueue(nodeQue, temp->rgt);
	}
	if (!temp->lft) temp->lft = newNode;
	else temp->rgt = newNode;
	DestroyTree(temp);
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

            Enqueue(nodeQue, temp->lft);
            Enqueue(nodeQue, temp->rgt);
            if (temp->lft)Enqueue(realnodeQue, temp->lft);
            if (temp->rgt)Enqueue(realnodeQue, temp->rgt);
        }
        else {
            printf("X ");
            Enqueue(nodeQue, NULL);
            Enqueue(nodeQue, NULL);
        }
    }
}