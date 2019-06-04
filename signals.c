/**
 * A Processes program Question 3 Ex 1 os.
 * @author Isreal Buskila and Moran Oshia
 * @since  2019-06
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/fcntl.h>
#include <sys/wait.h>

int prevPID =0;

//This function will be calld as a reaction to catching a signal.
void sigCathcher(int signal)
{

		printf("PID %d caught one \n", getpid());
		if(prevPID!=0){
			
			if(kill((getpid()-1),SIGINT)<0) {

                printf("\n Error do not sucsses %d\n",getpid());

                exit(1);

            }

		}
		sleep(1);
		exit(1);

};

int pid[5];
int ind = 0;
int pID;

int main (char **argv, int argc)
{


for (int i = 0; i < 5; i++)
    {
		
		pID=fork();
		pid[ind]=pID;
		ind++;
        if (pID< 0){
			perror("error of fork function");
			exit(1);
		}
		
		
		if (pID == 0)
        {
			
			prevPID=pid[i-1];
			signal(SIGINT, sigCathcher);
            printf("PID %d ready \n", getpid());
            break;
        }
   
	}
	sleep(1);
	

    if(pid[4]==0) {

        while(1);

    } 
	//killing zombies
	else if(pid[4]>0){
		int status;
		pid_t dead ;
		sleep(1);

        kill(pid[4],SIGINT);

        

        for(int i=0; i<5; i++) {

            dead=waitpid(pid[i], &status, 0);

            printf("Process %d is dead \n",dead);

        }

        exit(1);
		
	}





}
