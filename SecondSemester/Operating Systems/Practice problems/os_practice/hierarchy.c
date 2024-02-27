#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc,char* argv[]){
	int p = 0;
	for(int i=0;i<3;i++){
		if(p==0){
			printf("I am child:%d\n",getpid());
			fork();
		}
		else{
			printf("I have waited for my child\n");
			wait(0);
		}
		printf("I have killed my child\n");
		wait(0);
	}
}
