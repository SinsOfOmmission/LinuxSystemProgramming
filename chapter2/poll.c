/*
|-----------------------------------------------------------------------| 
|[root@localhost chapter2]# ./poll                                      |
|hello                                                                  |
|read from STDIN:hello                                                  |
|hello                                                                  |
|i                                                                      |
|.read from STDIN:i                                                     |
|llo                                                                    |
|i                                                                      |
|llo                                                                    |
|                                                                       |
|.read from STDIN:                                                      |
|                                                                       |
|llo                                                                    |
|                                                                       |
|                                                                       |
|llo                                                                    |
|                                                                       |
|-----------------------------------------------------------------------|
Run the binary,the mechanism of printf will explain the stange output.
Function printf has a buffer. 
The buffer content would be flushed to STDOUT_FILENO when the buffer is filled.
And the content forward the character '\n'(including the '\n') would be flushed to STDOUT_FILENO immediately when character '\n' was detected in the content.   

*/

#include<stdio.h>
#include<unistd.h>
#include<poll.h>

#define TIMEOUT 5

char cReadBuffer[1024] = {'*'};
int main(void)
{
    struct pollfd fds[2];
    int ret;
    int iReadLen;
    cReadBuffer[0] ='\0';

while(1)
{
    fds[0].events = POLLIN;
    fds[0].fd = STDIN_FILENO;

    fds[1].events = POLLOUT;
    fds[1].fd = STDOUT_FILENO;

    ret = poll(fds,2,TIMEOUT*1000);
    if (-1 == ret)
    {
        perror("poll");
        return 1;
    }

    if(!ret)
    {
        printf("%d seconds elapsed.\n",TIMEOUT);
        return 0;
    }

    if(fds[0].revents & POLLIN)
    {
        iReadLen = read(STDIN_FILENO,cReadBuffer,sizeof(cReadBuffer));
        if(-1 != iReadLen)
        {
            printf("read from STDIN:%s.",cReadBuffer);
        }
    }

    if(fds[1].revents & POLLOUT)
    {
        if('\0' != cReadBuffer[0])
        {
            if(-1 == write(STDOUT_FILENO,cReadBuffer,sizeof(cReadBuffer)) )
            {
                perror("write");
            }
            cReadBuffer[0] = '\0';
        }
    }
 }
    return 0;
}
