#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

char buffer[32] = {0};
int is_god = 0;


void usage(char* prog)
{
    printf("The ultimate password checker.\nUsage: %s <password>\n", prog);
}


char* md5sum(char* string)
{
    unsigned char digest[16] = {0};
    char* digest_str = malloc(33);
    memset(digest_str, 0, 33);
    MD5((unsigned char*)string, strlen(string), digest);

    for (int i = 0; i < 16; ++i)
    {
        sprintf(digest_str + i * 2, "%02x", digest[i]);
    }

    return digest_str;
}


int main(int argc, char** argv)
{
    char checksum_1[33] = {0};

    if (argc != 2)
    {
        usage(argv[0]);
        return 1;
    }
    puts("Everything is global now. Much more secure!");
    puts("Performing a password check...");

    strcpy(checksum_1, "b9c1dcb84084183ea55ebfe2bb077f82");
    strcpy(buffer, argv[1]);
    if (strlen(buffer) > 32)
    {
        buffer[32] = '\x00';
    }
    unsigned char* checksum_0 = md5sum(buffer);

    if (!strcmp(checksum_0, checksum_1) || is_god)
    {
        puts("Awesome job!");
        system("/bin/sh");
    }
    else
    {
        puts("Incorrect password. Try again.");
        return 0;
    }
}
