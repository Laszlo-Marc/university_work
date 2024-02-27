#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int main( int argc,char *argv[]){
	int p[2];
	if (-1 == pipe(p)){
		perror("Error on pipe");
		exit(1);
	}
	int f=fork();
	if(0>f){
		perror("Error on create child proccess");
		exit(1);
	}
	else if(0 == f){
		//child
		close(p[0]);
		if (-1==dup2(p[1],1)){
			perror("Error on dup2");
			exit(1);
		}
		if(-1==execvp(argv[1],argv+1)){
			perror("Error on command");
			close(p[1]);
			exit(1);
		}
		close(p[1]);
                exit(0);   
	}
	else{
		//parent
		close(p[1]);
		char *buf=malloc(sizeof(char) * 101);
		memset(buf,0,sizeof(char)*101);
		int k;
		while((k=read(p[0],buf,sizeof(char)*100))>0)
		{
			buf[k]=0;
			printf("%s",buf);
			//memset(buf,0,sizeof(char)*101);
		}
		free(buf);
		close(p[0]);
		wait(0);
	}
	return 0;
}
