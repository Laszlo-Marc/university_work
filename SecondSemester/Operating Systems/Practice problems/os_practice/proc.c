#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc,char* argv[]){
	if(fork() != fork())
		fork();
	printf("Current id: %d,parent id: %d\n",getpid(),getppid());
	return 0;
}
