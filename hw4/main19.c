#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{
  char buf[1024] = {0};
  int i, j;

  if (argc < 2) {
    fprintf(stderr, "Not enough arguments!\n");
    fprintf(stderr, "Usage: %s name_to_find\n", argv[0]);
    return 1;
  }

  // Filtering
  for (i = 1; i < argc; i++)
  {
    for (j = 0; j < strlen(argv[i]); j++)
    {
      if ((argv[i][j] == ';'))
      {
        // Someone told me that semicolons are bad bad bad
        fprintf(stderr, "Input contains prohibited characters\n");
        return 2;
      }
    }
  }

  for (i = 1; i < argc; i++) {
    snprintf(buf, 1023, "/usr/bin/find /home -iname %s", argv[i]);
    system(buf);
  }

  exit(0);
}
