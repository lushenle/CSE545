#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(char* prog)
{
    printf("The ultimate password checker.\nUsage: %s <password>\n", prog);
}


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        usage(argv[0]);
        return 1;
    }
    puts("Performing a password check...");
    if (!strcmp(argv[1], "TheGreatPassw0rd"))
    {
        puts("Welcome!\n");
        system("/bin/sh");
    }
    else
    {
        puts("Incorrect password. Try again.\n");
        return 0;
    }
}
