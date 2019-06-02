
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#define SIGCATHCHER 1;
int p;
void sighandler(int signum) {

   
        printf("PID %d caught one \n", getpid());
		
		if(p!=0){
			
			if(kill((getpid()-1),SIGINT)<0) {

                printf("\n Do not sucsses to kill %d\n",getpid());

                exit(1);

            }

		}
		
		sleep(2);
		exit(1);
		
    

}

int main () {

	int i=0;
	pid_t  pid;
	pid_t fd[5];
	

	for(int j=0;j<5;j++){
		
		pid=fork();
		
		
		if(pid>0){
			
			fd[i]=pid;
			i++;
		}
		
		else{
			p=i;
			signal(SIGINT, sighandler);
			if (signal(SIGCATHCHER, sighandler) == SIG_ERR)

                printf("\n fail singal \n");
            printf("PID %d ready \n",getpid());

          
			break;
		}
		
		
	}
	if(pid==0) {

        while(1);

    } 
	
	else if(pid>0){
		int status;
		pid_t dead ;
		sleep(2);

        kill(pid,SIGINT);

        

        for(int i=0; i<5; i++) {

            dead=waitpid(fd[i], &status, 0);

            printf("%d is dead \n",dead);

        }

        exit(1);
		
	}





}
