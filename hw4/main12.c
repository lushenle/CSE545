#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


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

  if (!strcmp(path, "/flag"))
  {
      printf("Cheater! You cannot bypass this defense by using the path to .secret!\n");
      return 1;
  }

  // Very important: Make sure this path does not point to a symlink
  // How did I miss this check in the previous level...
  struct stat the_stat;
  int r = stat(path, &the_stat);
  if (S_ISLNK(the_stat.st_mode))
  {
      printf("Cheater! You cannot bypass this defense by using a symlink file!\n");
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
