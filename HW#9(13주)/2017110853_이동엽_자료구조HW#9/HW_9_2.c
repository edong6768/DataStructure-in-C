#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Merge(int* arr, int i, int m, int n){
	int j=m+1, k=i, t, sorted[100];
  int low=i, high=n;
	while(i<=m&&j<=n){
		if(arr[i]<arr[j]) sorted[k++]=arr[i++];
		else sorted[k++]=arr[j++];
	}
	if(i>m){
		for(t=j;t<=n;t++){sorted[k+t-j]=arr[t];}
	} else{
		for(t=i;t<=m;t++){sorted[k+t-i]=arr[t];}
	}
  for(int s=low;s<=high;s++){arr[s]=sorted[s];}
}
void MergeSort(int* arr, int low, int high){
	int mid;
	if(low<high){
		mid=(low+high)/2;
		MergeSort(arr, low, mid);
		MergeSort(arr, mid+1, high);
		Merge(arr, low, mid, high);
	}
}
void Quick_Recur(int* arr,int low, int high){
	int piv, i=0, j=0, temp;
	if(low<high){
		i=low+1; j=high;
		piv = arr[low];
		do{
			for(;arr[i]<piv;i++);
			for(;arr[j]>piv;j--);
			if(i<j){
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}while(i<j);
		temp=arr[low];
		arr[low]=arr[j];
		arr[j]=temp;
		Quick_Recur(arr, low, j-1);
		Quick_Recur(arr, j+1, high);
	}
}

int main(){
	FILE* in;
	int mode=5, idx=0, arr[100], temp, minIDX;
	char fileN[50], str[300];
	char* token;

	printf("Input file name : ");
	scanf("%s",fileN);
	in=fopen(fileN,"r");

	if(!in){
		printf("File does not exists. Program terminates.");
		exit(0);
	}
	fseek(in,0,SEEK_END);
	if(!ftell(in)){
		printf("Nothing stored in file. Program terminates.");
		exit(0);
	}
	fseek(in,0,SEEK_SET);

	while(!feof(in)){
		fscanf(in, "%d",&arr[idx++]);
	}
	fclose(in);

	while(mode>4||mode<0){
		while(getchar()!='\n');
		printf("\nChoose a sorting method to use (Selection : 0, Insertion : 1, Bubble : 2, Quick : 3, Merge : 4 ) : ");
		scanf("%d",&mode);
		if(mode>4) printf("Enter from given list\n");
	}
	
	switch(mode){
	case 0:
		for(int i=0, j, min; i<idx-1;i++){
			for(j=i, min=1000;j<idx;j++){
				if(min>arr[j]){
					minIDX=j;
					min=arr[j];
				}
			}
			temp=arr[minIDX];
			arr[minIDX]=arr[i];
			arr[i]=temp;		
		}
		break;
	case 1:
		for(int i=1, j; i<idx;i++){
			temp=arr[i];
			for(j=i;temp<arr[j-1]&&j>0;j--){arr[j]=arr[j-1];}
			arr[j]=temp;
		}
		break;
	case 2:
		for(int i=0, j, sortcheck=0;i<idx&&!sortcheck;i++){
			for(j=idx-1, sortcheck=1;j>i;j--){
				if(arr[j]<arr[j-1]){
					sortcheck=0;
					temp=arr[j];
					arr[j]=arr[j-1];
					arr[j-1]=temp;
				}
			}
		}
		break;
	case 3:
		Quick_Recur(arr, 0, idx-1);
		break;
	case 4:
		MergeSort(arr, 0, idx-1);
		break;
	default:
		break;	
	}
	printf("The numbert sorted : %d",arr[0]);
	for(int i=1;i<idx;i++){
		printf(", %d",arr[i]);
	}
}