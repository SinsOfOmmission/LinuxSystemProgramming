#include<unistd.h>
#include<stdio.h>
main(int argc, char* argv[])
{
    printf("run myecho\n");
    int i;
    for(i = 0; i < argc; ++i)
	printf("argv[%d]:%s\n", i, argv[i]);
}
