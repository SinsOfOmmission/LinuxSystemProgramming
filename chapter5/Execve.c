#include<unistd.h>
#include<assert.h>
main(int argc, char* argv[])
{
    char *argvs[] = {"hello","world",NULL};
    char *envp[] = {NULL};
    assert(2 == argc);
//    argvs[0] = argv[1];
    execve(argv[1],argvs,envp);
    perror("execve");
}
