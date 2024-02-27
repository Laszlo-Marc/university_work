#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void f(int n){
	int n,i;
	for(i=0;i<=n;i++){
		f=fork();
		if(f==0){
			printf("PID=%d - PPID=%d\n",getpid(),getppid());
			f(n-1);
		} 
		else if(f==-1){
			printf("Fork error");
			exit(1);
		}
	}
	wait(0);
	exit(0);
}

int main(int argc,char* argv[]){
	f(3);
	return 0;
}
