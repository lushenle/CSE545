/* WARNING: Could not reconcile some variable overlaps */

int main(int argc,char **argv)

{
  size_t sVar1;
  long lVar2;
  undefined8 *puVar3;
  char buf [1024];
  int j;
  int i;

  buf._0_8_ = 0;
  buf._8_8_ = 0;
  puVar3 = (undefined8 *)(buf + 0x10);
  for (lVar2 = 0x7e; lVar2 != 0; lVar2 = lVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  if (1 < argc) {
    i = 1;
    do {
      if (argc <= i) {
        for (i = 1; i < argc; i = i + 1) {
          snprintf(buf,0x3ff,"/usr/bin/find /home -iname \"%s\"",argv[i]);
          system(buf);
        }
                    /* WARNING: Subroutine does not return */
        exit(0);
      }
      for (j = 0; sVar1 = strlen(argv[i]), (ulong)(long)j < sVar1; j = j + 1) {
        if ((((argv[i][j] == ';') || (argv[i][j] == '$')) || (argv[i][j] == '|')) ||
           (((argv[i][j] == '`' || (argv[i][j] == '<')) ||
            ((argv[i][j] == '>' || (argv[i][j] == '&')))))) {
          fwrite("Input contains prohibited characters\n",1,0x25,stderr);
          return 2;
        }
      }
      i = i + 1;
    } while( true );
  }
  fwrite("Not enough arguments!\n",1,0x16,stderr);
  fprintf(stderr,"Usage: %s name_to_find\n",*argv);
  return 1;
}
