#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
int pid=fork();
if(pid>0){
printf("\n i am parent process");
printf("\n pid=%d \n",getppid());
}
else if(pid == 0){
printf("\ni am child process");
printf("\n pid=%d",getpid());
}
}