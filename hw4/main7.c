#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


void usage(char* prog)
{
    printf("The ultimate password checker.\nUsage: %s <password>\n", prog);
}


char* md5sum(char* string)
{
    char in_path[120];
    char out_path[120];

    srand(time(0));
    int randnum = (rand() << 15) | rand();

    sprintf(in_path, "/tmp/md5sum_input_%d_%d", getuid(), randnum);
    sprintf(out_path, "/tmp/md5sum_result_%d_%d", getuid(), randnum);

    // Write input to a file
    FILE* fp = fopen(in_path, "wb");
    if (fp == NULL)
    {
        fprintf(stderr, "Cannot open the md5 input file.\n");
        return NULL;
    }
    fwrite(string, strlen(string), 1, fp);
    fclose(fp);

    char cmd[200];
    sprintf(cmd, "/usr/bin/md5sum %s > %s", in_path, out_path);

    system(cmd);
    puts("Wait for 2 seconds so that the file is definitely updated...");
    sleep(2);
    unlink(in_path);

    fp = fopen(out_path, "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "Cannot open the md5 output file.\n");
        return NULL;
    }
    char buf[33] = {0};
    fread(buf, 32, 1, fp);
    fclose(fp);
    unlink(out_path);

    char *digest = malloc(33);
    memset(digest, 0, 33);
    strcpy(digest, buf);
    return digest;
}


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        usage(argv[0]);
        return 1;
    }
    puts("This level is updated to fix conflicts between users.");
    puts("This time, your uid is part of the file name!");
    printf("Your real UID is %d. This number is now part of the file path.\n", getuid());
    puts("");
    puts("OK... I am not sure how to make a secure password checker...");
    puts("But let me try one last time!");
    puts("I will use the best md5sum utility provided by Linux. IT IS GREAT.");
    puts("#################################");
    puts("Performing a password check...");

    char* checksum_0 = md5sum(argv[1]);
    char* checksum_1 = "5bbbbc107dd9c0ee0b6503025bafca6e";

    if (checksum_0 == NULL)
    {
        puts("Cannot open the checksum file.\n");
        return 1;
    }
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
