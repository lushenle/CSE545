#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
  FILE *f;
  char *path = NULL;
  char buf1[33];
  char buf2[33];
  int i;

  if (getenv("BASE") == NULL)
  {
      fprintf(stderr, "Missing environment variable.\n");
      return 1;
  }
  int buffer_length = strlen(getenv("BASE")) + 9;
  path = malloc(buffer_length);
  sprintf(path, "%s/flag", getenv("BASE"));

  // I missed an important check in the previous level.
  if (!strcmp(path, "/flag"))
  {
      printf("Cheater! You cannot bypass the most solid check!\n");
      return 1;
  }

  f = fopen(path, "rb");
  if (f == NULL)
  {
      perror("fopen");
      fprintf(stderr, "Cannot open %s.\n", path);
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
