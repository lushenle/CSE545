#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int write_data(unsigned long long canary, char* data)
{
    FILE *f = NULL;
    char filename[256];
    unsigned long long saved_canary = canary;
    register long long rsp asm ("rsp");

    printf("Here is a stack pointer for you: %llx\n", rsp);

    read(0, filename, 273);
    if (access(filename, W_OK)) {
        goto error;
    }

    if (strncmp(filename, "/tmp/", strlen("/tmp/")) != 0) {
        goto error;
    }

    if ((f = fopen(filename, "a")) == NULL) {
        goto error;
    }

    fwrite(data, strlen(data), 1, f);
    fclose(f);

error:
    if (saved_canary != canary) {
        printf("Hacking attempts detected!\n");
        exit(-2);
    }
    return 0;
}

int main(int argc, char **argv)
{
    // Load a stack canary
    FILE *f = fopen("/challenge/level43_canary", "rb");
    unsigned long long canary = 0;

    if (f == NULL) {
        printf("Failed to load the stack canary. Use a random number instead.\n");
        canary = 0xdeadbeefdeadbeef;
    } else {
        fread((void*)&canary, 8, 1, f);
        fclose(f);
    }

    return write_data(canary, argv[1]);
}
