#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/fcntl.h>

//This function will be calld as a reaction to catching a signal.
void catchSigT(int sig_num)
{

signal(SIGTERM, catchSigT);

};
int pid[5];
int i = 0;


int main (char **argv, int argc)
{


signal(SIGTERM, catchSigT);

pid[0] = fork();
if(pid[0] != 0)
pid[1] = fork();
if(pid[1] != 0)
pid[2] = fork();
if(pid[2] != 0)
pid[3] = fork();
if(pid[3] != 0)
pid[4] = fork();



if(pid[0] == 0 || pid[1] == 0 ||pid[2] == 0 || pid[3] == 0|| pid[4] == 0){
printf("pid %d ready\n", getpid());


}
sleep(1);
if(pid[0] == 0 || pid[1] == 0 ||pid[2] == 0 || pid[3] == 0|| pid[4] == 0){
kill(pid[i++],SIGTERM);
printf("pid %d caught one\n",getpid());
}
sleep(0.75);


if(pid[0] == 0 || pid[1] == 0 ||pid[2] == 0 || pid[3] == 0|| pid[4] == 0)
printf("process %d is dead\n",getpid());
kill(getpid(), SIGINT);

return 0;





}
