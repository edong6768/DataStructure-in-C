#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	FILE* in;
	int mode=3, idx=0, arr[100], elm, curr, step, count, low, high;
	int* hash=(int*)calloc(100,sizeof(int));
	char fileN[50], str[300];
	char* token;

	printf("Input file name : ");
	scanf("%s", fileN);
	in = fopen(fileN, "r");

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

	for(int i=0,j=arr[i]%100;i<idx;i++,j=arr[i]%100){
		while(hash[j]){
			j=(j+1)%100;
		}
		hash[j]=arr[i];
	}

	printf("Target integer : ");
	scanf("%d",&elm);

	while(mode>2||mode<1){
		while(getchar()!='\n');
		printf("\n\nChoose a searching method (Binary : 1, Hashed : 2) : ");
		scanf("%d",&mode);
		if(mode>2||mode<1) printf("Enter from given list\n");
	}

	switch(mode){
	case 1:
		for(int i=1, j, temp; i<idx;i++){
			temp=arr[i];
			for(j=i;temp<arr[j-1]&&j>0;j--){arr[j]=arr[j-1];}
			arr[j]=temp;		
		}
		for(curr=idx/2,step=idx/4, low=0, high=idx-1;arr[curr]!=elm&&high-low!=1;step=(step>1)?step/2:1){
			if(arr[curr]>elm){
				high=curr;
				curr-=step;
			}
			else{
				low=curr;
				curr+=step;
			}
		}
		if(arr[curr]==elm) printf("%d is found!", elm);
		else printf("%d is not found!", elm);
		break;
	case 2:
		for(curr=elm%100, count=0;hash[curr]!=elm&&hash[curr]&&count<100;count++,curr+=(curr<idx-1)?1:(-idx+1));
		if(hash[curr]==elm) printf("%d is found!", elm);
		else printf("%d is not found!", elm);
		break;
	default:
		break;	
	}
}