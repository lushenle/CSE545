#include <stdio.h>

void usage(char *prog)

{
    printf("The ultimate password checker.\nUsage: %s <password>\n",prog);
    return;
}

uchar * md5sum(char *string)

{
    uchar *md;
    size_t n;
    uchar *digest;

    md = (uchar *)malloc(0x10);
    n = strlen(string);
    MD5((uchar *)string,n,md);
    return md;
}

int main(int argc,char **argv)

{
    int iVar1;
    size_t sVar2;
    uchar *__s1;
    uchar *checksum_0;

    if (argc == 2) {
        puts("Everything is global now. Much more secure!");
        puts("Performing a password check...");
        checksum_1._0_8_ = 0x630bbf3db8b42856;
        checksum_1._8_8_ = 0xf78111bc9a24e23d;
        sVar2 = strlen(argv[1]);
        if (0x20 < sVar2) {
            argv[0x20] = (char *)0x0;
        }
        strcpy(buffer,argv[1]);
        __s1 = md5sum(buffer);
        iVar1 = strcmp((char *)__s1,(char *)checksum_1);
        if (iVar1 == 0) {
            puts("Awesome job!");
            system("/bin/sh");
            iVar1 = 0;
        }
        else {
            puts("Incorrect password. Try again.");
            iVar1 = 0;
        }
    }
    else {
        usage(*argv);
        iVar1 = 1;
    }
    return iVar1;
}
