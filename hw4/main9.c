#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
  FILE *f;
  char buf1[33];
  char buf2[33];
  int i;

  system("/bin/cat ~/flag > level9_secret");
  f = fopen("level9_secret", "rb");
  if (f == NULL)
  {
      perror("fopen");
      fprintf(stderr, "Cannot open level9_secret.");
      return 1;
  }
  if ((i = fread(buf1, 1, 32, f)) == 0)
  {
    perror("fread");
    return 1;
  }
  buf1[i] = '\0';

  f = fopen("/flag", "r");
  if ((i = fread(buf2, 1, 32, f)) == 0)
  {
    perror("fread");
    return 1;
  }
  buf2[i] = '\0';

  if (!strcmp(buf1, buf2)) {
    execl("/bin/sh", "/bin/sh", (void *)NULL);
  }

  fprintf(stderr, "Wrong password!\n");
  return 0;
}
