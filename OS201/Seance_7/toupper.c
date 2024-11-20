#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

char in_buffer[1024];

int main()
{
    int pid = getpid();
    char hostname[100];
    gethostname(hostname, 100);
    while(1){
        if(fgets(in_buffer, 1024, stdin) == NULL) break;
        char* ptr = in_buffer;
        while(*ptr){*ptr = toupper(*ptr); ptr++;}
        sleep(3);
        printf("On %s pid %d answer %s\n", hostname, pid, in_buffer);
        fflush(stdout);
    }

    return 0;
}