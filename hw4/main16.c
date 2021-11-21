#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char **argv)
{
  printf("The best XHTML-compliance checker you have on this planet.\n");

  if (argc != 2 || argv[1] == NULL) {
    fprintf(stderr, "Please specify the file to verify\n");
    return 1;
  }

  // This must be super super super secure
  if (strchr(argv[1], '"') != NULL)
  {
      fprintf(stderr, "You are a bad bad bad attacker. Do not attempt command injection!\n");
      return 1;
  }

  char *cmd = NULL;
  cmd = malloc(strlen(argv[1]) + 30);
  sprintf(cmd, "/usr/bin/tidy -asxml \"%s\"", argv[1]);

  system(cmd);
  perror("execlp");
  return 1;
}
