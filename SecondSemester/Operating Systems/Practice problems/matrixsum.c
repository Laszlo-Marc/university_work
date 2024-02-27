#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_SIZE 10
int main(int argc,char* argv[]){
	int n,k,i,j,pid,status;
	int matrix1[MAX_SIZE][MAX_SIZE],matrix2[MAX_SIZE][MAX_SIZE],result[MAX_SIZE][MAX_SIZE];
	FILE *fp;
	int pipefd[2];	
	if(argc !=2){
		fprintf(stderr,"Usage: %s input file\n",argv[0]);
		exit(1);
	}

	fp = fopen(argv[1],"r");
	if(fp==NULL){
		perror("fopen");
		exit(1);
	}

	fscanf(fp,"%d",&n);

	for(i=0;i<=n;i++){
		for(j=0;j<=n;j++){
			fscanf(fp,"%d",&matrix1[i][j]);}
	}


        for(i=0;i<=n;i++){
                for(j=0;j<=n;j++){
                        fscanf(fp,"%d",&matrix2[i][j]);}
        }
	

	fclose(fp);
	if (pipe(pipefd) == -1){
		perror("pipe");
		exit(1);
	}

	pid = fork();

	if(pid == -1){
		perror("fork");
		exit(1);
	}

	if(pid == 0){
		close(pipefd[0]);
		for(i=0;i<=n;i++){
                	for(j=0;j<=n;j++){
				result[i][j]=0;
				for(k=0;k<n;k++){
					result[i][j] += matrix1[i][k] * matrix2[k][i];}
			       
			}
		}
		write(pipefd[1],result,sizeof(result));
		close(pipefd[1]);
		exit(0);
	}else{
		close(pipefd[1]);
		wait(&status);
		read(pipefd[0],result,sizeof(result));
		close(pipefd[0]);
		printf("Result matrix: \n");
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				printf("%d",result[i][j]);
			}
			printf("\n");
		}
	}
	return 0;

}

