#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char comm[80],*args[5];
int main(){
	while(1){
		printf("\n myshell$ ");
		get_comm();
		sep_args();
		take_action();
	}
	return 0;
}
void get_comm(){
	int len;
	len = strlen(comm);
	fgets(comm,80,stdin);
	comm[len-1] = '\0';
}
void sep_args(){
	int i,j=0,t=0;
	args[t] = (char*) malloc(sizeof(char)*20);
	
	for(i=0;comm[i]!='\0';i++){
		if(comm[i]==' '){
			args[t][j]='\0';
			t++;
			j=0;
			args[t] = (char*) malloc(sizeof(char)*20);
		}
		else{
			args[t][j] = comm[i];
			j++;
		}
	}
	args[t][j]='\0';
}
void take_action(){
	if(strcmp(args[0],"search")==0){
		search(args[1][0],args[2]);
	}
	else{
		printf("\n Command not found",args[0]);
	}
}
void search(char op, char fname[]){
	char buff[100],*ptr,*pattern="include";
	int cnt,i;
	FILE *fp;

	fp= fopen(fname,"r");
	if( fp == NULL ){
		printf("\n Unable to open file");
		return ;
	}
	
	if(op=='a'){
		while (!feof(fp)){
			buff[0] = '\0';
			fgets(buff,80,fp);
			ptr = strstr(buff,pattern);
			if( ptr != NULL )
				printf("%s",buff);
		}
		fclose(fp);
	}
	else if(op=='f'){
		while (!feof(fp)){
			buff[0] = '\0';
			fgets(buff,80,fp);
			ptr = strstr(buff,pattern);
			if( ptr != NULL ){
				printf("%s",buff);
				break;
			}
		}
		fclose(fp);
	}
	else if(op=='c'){
		cnt=0;
		while (!feof(fp))
		{
			buff[0] = '\0';
			fgets(buff,80,fp);
			ptr = strstr(buff,pattern);
			if( ptr != NULL )
				cnt++;
		}
		fclose(fp);
		printf("\n %d ",cnt);
	}
	else{
		printf("\n Invalid Option");
	} 
}
