#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>


void usage(char* prog)
{
    printf("The ultimate password checker.\nUsage: %s <password>\n", prog);
}


unsigned char* md5sum(char* string)
{
    unsigned char *digest = malloc(16);
    MD5((unsigned char*)string, strlen(string), digest);
    return digest;
}


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        usage(argv[0]);
        return 1;
    }
    puts("Oops, I know using a well-known phrase as my password is a bad thing... Fixed this time!");
    puts("Performing a password check...");

    unsigned char* checksum_0 = md5sum(argv[1]);
    unsigned char* checksum_1 = "\xb4\x9f\xb9\x0a\x92\xca\x0c\x28\xb8\x45\x08\xe4\x77\x37\xc5\x49";
    int len_0 = strlen(checksum_0);
    int len_1 = strlen(checksum_1);

    if (!strncmp(checksum_0, checksum_1, len_0 < len_1? len_0: len_1))
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
