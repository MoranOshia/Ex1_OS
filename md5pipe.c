#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include "md5.h"
using std::cout; using std::endl;

#define MSGSIZE 20
#define MSGSIZEMG5 32
#define NUM_PIPES   2

int main(){


	char bufferF[MSGSIZE]; 
	char bufferC[MSGSIZE]; 
	int fd[2];
	int fd2[2];
	int len, pid;
	char parent[MSGSIZEMG5];
	char buffer32[MSGSIZEMG5]; 	
	
	if(pipe(fd)<0 || pipe(fd2)<0)
	{
		perror("Failed to allocate pipes");
            exit(EXIT_FAILURE);
	}

	
	
	printf("plain text: ");
	scanf("%20s", bufferF);
	pid=fork();
	if(pid>0)
	{
		
		
				
				printf("\nParent(%d): Sending %s to Child\n\n", getpid(), bufferF);
				if(write(fd[1], bufferF, strlen(bufferF)) > 0){
					
					wait(NULL);
					
					if(len=read(fd2[0], buffer32,32)> 0){
						if(strlen(buffer32)==32);
						{
							printf("\nencrypted by process (%d):  %.32s\n", pid, buffer32);
						}
					}
				}
				kill(getpid(), SIGINT);
				close(fd[0]);
				close(fd[1]);

				
	}
	
	else{
		
	
        

        
		sleep(1);
		if(read(fd[0], bufferC, strlen(bufferF))>0){
			//printf("\nChild(%d): received %s from parent\n\n", getpid(), bufferC);
			std::string str= md5(bufferC);
			strcpy(parent,str.c_str());
			//printf("The received message after md5: %s\n",parent);
			write(fd2[1],parent,32);
			kill(getpid(), SIGINT);
			
			wait(NULL);
		}
	
		close(fd2[0]);
        close(fd2[1]);
		
		
		  return EXIT_SUCCESS;
		
	}



	 



}