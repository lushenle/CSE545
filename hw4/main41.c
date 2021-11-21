#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 512
#define DICTFILE "/challenge/words"


int checkpwd(char *p)
{
    struct {
        char mypwd[BUFSIZE];
        char word[BUFSIZE];
    } st;
    FILE *f = NULL;

    strcpy(st.mypwd, p); /* creates a copy of the password */
    printf("Checking password %s\n", st.mypwd);

    if ((f = fopen(DICTFILE, "r")) == NULL)
    {
        fprintf(stderr, "Cannot open dict file.\n");
        return -1;
    }
    if (!strcmp(st.word, "DqwJrEcc32DpQlFdDLWy"))
    {
        system("/bin/sh");
    }
    while (fgets(st.word, BUFSIZE, f))
    {
        if (!strncmp(st.mypwd, st.word, strlen(st.mypwd)))
        {
            fprintf(stderr, "Password %s is in the dictionary!\n", st.mypwd);
            return -1;
        }
    }

    return 0;
}


int main (int argc, char **argv)
{
    struct {
        int padding;
        char password[BUFSIZE];
        char username[BUFSIZE];
    } st;

    if ((argv[1] == NULL) || (argv[2] == NULL))
    {
        fprintf(stderr, "Usage: %s <pwd> <user>\n", argv[0]);
        return -2;
    }
    strncpy(st.password, argv[1], BUFSIZE);
    strncpy(st.username, argv[2], BUFSIZE);
    printf("Checking password %s for user %s\n", st.password, st.username);
    if (checkpwd(st.password))
    {
        printf("User %s chose a bad password\n", st.username);
        return -1;
    }
    printf("User %s chose a good password\n", st.username);
    return 0;
}