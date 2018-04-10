#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
main()
{
pid_t pCurPid = getpid();
pid_t pCurPPid = getppid();
printf("This progress PID:%d\n",pCurPid);
printf("This progress's parent progress PID:%d\n",pCurPPid);
}
