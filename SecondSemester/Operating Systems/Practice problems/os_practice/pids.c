#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main(int argc,char* argv[]){
	int id = fork();
	if(id==0){
		sleep(1);
	}
	printf("Current id: %d,parent id:%d\n",getpid(),getppid());
	wait(0);
	return 0;
}

