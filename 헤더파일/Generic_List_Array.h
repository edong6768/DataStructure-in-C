#include <stdlib.h>

typedef struct {
    void** data;
    int size, rear, pos;
    int (*compare)(void* data1, void* data2);
}List;

List* CreateList(int (*compare)(void* data1, void* data2), int size) {
    List* newList = (List*)malloc(sizeof(List));
    if (newList == NULL) return NULL;

    newList->data = (void**)malloc(size * sizeof(void*));
    if (newList->data == NULL) {
        free(newList->data);
        return NULL;
    }

    newList->size = size; newList->rear = 0; newList->pos = 0;
    newList->compare = compare;
    return newList;
}


int _searchNode(List* list, void* data) {
    int i;
    for (i = 0; i < list->rear; i++) {
        if (list->compare(list->data[i], data) == 0) return -i - 1;
        else if (list->compare(list->data[i], data) > 0) break;
    }
    return i;
}

void AddList(List* list, void* data) {
    int pos = _searchNode(list, data);
    if (pos < 0) return;

    if (list->size <= pos || list->size == list->rear) return;
    for (int i = list->rear; i >= pos; i--) {
        list->data[i + 1] = list->data[i];
    }
    list->data[pos] = data;
    if (list->pos > pos)list->pos++;
    list->rear++;
}

void RemoveList(List* list, void* data) {
    int pos = _searchNode(list, data);
    if (pos >= 0) return;

    if (list->size <= (-pos-1) || list->rear == 0) return;
    for (int i = -pos-1; i < list->rear; i++) {
        list->data[i] = list->data[i + 1];
    }
    if (list->pos > pos)list->pos--;
    list->rear--;
}

int SearchList(List* list, void* data) {return (_searchNode(list, data) <0) ? 1 : 0;}


int TraverseList(List* list, int fromWhere, void** pDataout) {
    if (fromWhere == 0) list->pos = 0;
    else list->pos++;
    if (list->pos == list->rear) {
        *pDataout = NULL;
        return 0;
    }
    *pDataout = list->data[list->pos];
    return 1;
}

void DestroyList(List* list) {
    for (int i = 0; i < list->rear; i++) {free(list->data[i]);}
    free(list->data);
    free(list);
}
