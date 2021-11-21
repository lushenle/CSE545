#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int write_data(char* data)
{
    FILE *f = NULL;
    char filename[256];
    register long long rsp asm ("rsp");

    printf("Here is a stack pointer for you: %llx\n", rsp);
    fflush(stdout);

    fgets(filename, 273, stdin);
    if (access(filename, W_OK)) {
        return -1;
    }

    if (strncmp(filename, "/tmp/", strlen("/tmp/")) != 0) {
        return -1;
    }

    if ((f = fopen(filename, "a")) == NULL) {
        return -1;
    }

    fwrite(data, strlen(data), 1, f);
    fclose(f);
    return 0;
}

int main(int argc, char **argv)
{
    return write_data(argv[1]);
}