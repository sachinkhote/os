#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

void insertSort(int arr[],int n){
	int i,j,temp;

	for(i=1;i<n;i++){
		temp = arr[i];
		
		for(j=i-1;j>=0 && arr[j]>temp;j--){
			arr[j+1] = arr[j];
		}
		arr[j+1] = temp;
	}
}

void bubbleSort(int arr[],int n){
	int i,j,temp;

	for(i=1;i<n;i++){
		for(j=0;j<n-i;j++){
			if(arr[j]>arr[j+1]){
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

int main(){
	int arr[100],n,i;
	pid_t pid;

	printf("\n Enter Array Size : ");
	scanf("%d",&n);

	printf("\n Enter %d Array Elements : ",n);
	for(i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}

	pid = fork();

	if(pid<0){
		printf("\n Error");
	}
	else if(pid==0){
		insertSort(arr,n);
		
		printf("\n\n Array Elements after Insert. Sort Using Child Process : ");
		for(i=0;i<n;i++){
			printf(" %d ",arr[i]);
		}
	}
	else{
		bubbleSort(arr,n);

		printf("\n\n Array Elements after Bubble Sort Using Parent Process : ");
		for(i=0;i<n;i++){
			printf(" %d ",arr[i]);
		}
	}
	return 0;
}