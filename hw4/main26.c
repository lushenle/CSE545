int main(int argc,char **argv)

{
  int iVar1;
  size_t sVar2;
  char *pcVar3;
  char buf [1024];
  int j;
  int i;

  if (argc < 2) {
    fwrite("Not enough args\n",1,0x10,stderr);
    iVar1 = 1;
  }
  else {
    i = 1;
    while( true ) {
      if (argc <= i) {
        for (i = 1; i < argc; i = i + 1) {
          snprintf(buf,0x3ff,"/usr/bin/find /home -iname \"%s\"",argv[i]);
          system(buf);
        }
                    /* WARNING: Subroutine does not return */
        exit(0);
      }
      for (j = 0; sVar2 = strlen(argv[i]), (ulong)(long)j < sVar2; j = j + 1) {
        if ((((((argv[i][j] == '&') || (argv[i][j] == '>')) || (argv[i][j] == '<')) ||
             ((argv[i][j] == '`' || (argv[i][j] == ';')))) || (argv[i][j] == '|')) &&
           ((j == 0 ||
            (((j != 1 || (*argv[i] == '\\')) &&
             ((argv[i][(long)j + -1] != '\\' || (argv[i][(long)j + -2] == '\\')))))))) {
          fwrite("Input contains prohibited characters\n",1,0x25,stderr);
          return 2;
        }
      }
      pcVar3 = strstr(argv[i],"flag");
      if (pcVar3 != (char *)0x0) break;
      i = i + 1;
    }
    fwrite("What are you trying to do???\n",1,0x1d,stderr);
    fwrite("Hacking attempt blocked!\n",1,0x19,stderr);
    iVar1 = 3;
  }
  return iVar1;
}
