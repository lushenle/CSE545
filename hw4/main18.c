#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{
  int pipefd[2];
  pid_t pid;
  int fd;
  int in;
  char c;
  int status;

  printf("The best XHTML-compliance checker you have on this planet.\n");

  if (argc != 2 || argv[1] == NULL) {
    fprintf(stderr, "Please specify the file to verify\n");
    return 1;
  }

  // The fundamental problem is that I am too nice and I am allowing the user to
  // interact with the `tidy` program.
  // This time no interaction is allowed! I am forking and overwriting the stdin
  // and stdout file descriptors in the child process before running `tidy`.

  if ((in = open(argv[1], O_RDONLY)) < 0) {
    perror("open");
    return 2;
  }

  if ((fd = open("/dev/null", O_RDWR)) < 0) {
    perror("open");
    return 5;
  }

  if (pipe(pipefd) < 0) {
    perror("pipe");
    return 3;
  }

  if ((pid = fork()) < 0) {
    perror("fork");
    return 4;
  }

  if (pid == 0) {
    dup2(pipefd[0], 0);
    dup2(fd, 1);
    dup2(fd, 2);

    close(pipefd[1]);
    close(fd);
    close(in);

    execlp("tidy", "tidy", "-asxml", NULL);
    perror("execlp");
    return 5;
  }

  while (read(in, &c, 1)) {
    write(pipefd[1], &c, 1);
  }

  close(pipefd[1]);
  close(pipefd[0]);
  close(fd);
  close(in);

  waitpid(pid, &status, 0);

  switch(WEXITSTATUS(status)) {
  case 0:
    printf("OK!\n");
    break;
  case 1:
    printf("Your file is not completely compliant\n");
    break;
  case 2:
    printf("Your file contains errors\n");
    break;
  default:
    printf("I can't tell if your file is XHTML-compliant\n");
  }

  return 0;
}
