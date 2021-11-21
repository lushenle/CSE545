#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

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
    if (argc != 2)
    {
        usage(argv[0]);
        return 1;
    }
    puts("Plain-text comparison is stupid. Hashed password checks are the future!");
    puts("Performing a password check...");

    char* checksum_0 = md5sum(argv[1]);
    char* checksum_1 = md5sum("py26jr5mmLktuNIy2Apt");

    if (!strcmp(checksum_0, checksum_1))
    {
        puts("Awesome job!");
        system("/bin/sh");
    }
    else
    {
        puts("Incorrect password. Try again.\n");
        return 0;
    }
}
