#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char **argv)
{
  printf("The best XHTML-compliance checker you have on this planet.\n");

  if (argc != 2 || argv[1] == NULL) {
    fprintf(stderr, "Please specify the file to verify\n");
    return 1;
  }

  // OK this time it is really really really safe
  execlp("tidy", "tidy", "-asxml", argv[1], NULL);
  perror("execlp");
  return 1;
}
