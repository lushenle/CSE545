int main(int argc,char **argv)

{
  int iVar1;
  char *pcVar2;
  anon_struct_for_st st;

  memset(&st,0,0x100);
  memset(st.filename,0,0x100);
  if (argv[1] == (char *)0x0) {
    fwrite("Please provide the program name. Currently available programs:\n",1,0x3f,stderr);
    system("ls echo level37");
    iVar1 = 2;
  }
  else {
    pcVar2 = __xpg_basename(argv[1]);
    snprintf(st.filename,0xff,"/challenge/%s",pcVar2);
    printf("Checking filename %s\n",st.filename);
    iVar1 = access(st.filename,1);
    if (iVar1 == 0) {
      if (argv[2] == (char *)0x0) {
        puts("Provide the parameter(s):");
        gets(st.buffer);
      }
      else {
        strcpy(st.buffer,argv[2]);
      }
      printf("Executing filename %s...\n",st.filename);
      execlp(st.filename,st.filename,&st,0);
      iVar1 = 0;
    }
    else {
      fwrite("You do not have the permission to execute this file\n",1,0x34,stderr);
      iVar1 = 1;
    }
  }
  return iVar1;
}
