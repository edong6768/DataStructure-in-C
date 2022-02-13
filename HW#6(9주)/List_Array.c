#include <stdio.h>
#include "Generic_List_Array.h"
#include "VoidCompare.h"

int main() {
	List* nums = CreateList(Compare_int,50);
	int mode;
	int* data;

	while (1) {
		data = (int*)malloc(sizeof(int));
		printf("\nIn (0), Search (1), Out (2), Exit (3) : ");
		scanf("%d", &mode);

		switch (mode) {
		case 0:
			printf("In : ");
			scanf("%d", data);
			AddList(nums, data);
			break;
		case 1:
			printf("Search : ");
			scanf("%d", data);
			printf("My List %s %d\n", (SearchList(nums, data)) ? "has" : "does not have", *data);
			break;
		case 2:
			printf("Out : ");
			scanf("%d", data);
      if(SearchList(nums, data)==1) printf("%d was removed\n",*data);
			RemoveList(nums, data);
			break;
		case 3:
			DestroyList(nums);
			exit(0);
		default:
			break;
		}

		printf("The current status of List :");
		for (int n = 0; TraverseList(nums, n, (void**)&data); n++) {
			printf("%s %d", (n) ? ", " : " ", *(int*)data);
		}
		printf("\n");
	}
}