char * md5sum(char *string)

{
    uchar *md;
    size_t n;
    char *digest;

    md = (uchar *)malloc(0x10);
    n = strlen(string);
    MD5((uchar *)string,n,md);
    return (char *)md;
}



void usage(char *prog)

{
    printf("The ultimate password checker - everything is on the stack.\nUsage: %s <password>\n",prog)
            ;
    return;
}


int main(int argc,char **argv)

{
    int iVar1;
    size_t sVar2;
    char *__s1;
    anon_struct_for_st st;
    uchar *checksum_0;

    memset(&st,0,0x20);
    memset(st.checksum_1,0,0x20);
    if (argc == 2) {
        puts("Performing a password check...");
        st.checksum_1._0_8_ = 0xfa66271dfee29f35;
        st.checksum_1._8_8_ = 0xbb13245530934104;
        st.checksum_1[16] = '\0';
        strcpy(st.buffer,argv[1]);
        sVar2 = strlen(st.buffer);
        if (0x20 < sVar2) {
            st.checksum_1._0_8_ = st.checksum_1._0_8_ & 0xffffffffffffff00;
        }
        __s1 = md5sum(st.buffer);
        iVar1 = memcmp(__s1,st.checksum_1,0x10);
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