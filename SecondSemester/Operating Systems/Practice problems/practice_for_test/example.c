#include <stdio.h>
#include <unistd.h>

int main(int argc,char *argv[]){
	printf("before\n");
	fork();
	printf("after\n");
	return 0;
}
