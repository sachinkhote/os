#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	pid_t pid;
	pid = fork();
	while(1){
		if(pid==0){
			printf("\n i am Child process,id=%d \n",getpid());
			printf("\n priority:%d",nice(-7),getpid());
		}
		else{
			printf("\n i am Parent process,id=%d",getpid());
			printf("\n priority :%d",nice(15),getpid());
		}
		return 0;
}
}