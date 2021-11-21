#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage()
{
    printf("The ultimate password checker.\n");
}


int main(int argc, char** argv)
{
    if (argc != 1)
    {
        usage();
        return 1;
    }
    puts("Performing a password check...");
    if (!strcmp(argv[0] + 2, "JyvPr6Tk52mTyqoSeQmx"))
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
