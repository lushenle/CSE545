#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <pwd.h>
#include <sys/errno.h>
#include <netdb.h>

#define CHUNK_SIZE 65536
//#define DEBUG

int mindex;

void reaper(int sig)
{
  int status;
  while (wait3(&status, WNOHANG, (struct rusage *)0) >= 0)
    {/* empty */}
}

int manage_tcp_client()
{
  char buffer[CHUNK_SIZE];
  int ret = 0;

  printf("Ready to read!\n");
  fflush(stdout);

  mindex = 0;
  while ((ret = read(0, &buffer[mindex], 1)) > 0) {
    mindex++;
#ifdef DEBUG
    fprintf(stderr, "mindex is %d\n", mindex);
#endif
    if (buffer[mindex - 1] == 0x0a) {
      buffer[mindex - 1] = '\0';
      break;
    }
  }

  if (ret < 0) {
    fprintf(stderr, "ERROR: read failed: %s\n", strerror(errno));
    return 1;
  }

  printf("Received: %s\n", buffer);
  printf("Done!\n");
  fflush(stdout);
  return 0;
}


int main(int argc, char *argv[])
{
  int sockfd;
  struct sockaddr_in client_addr;
  struct sockaddr_in server_addr;
  int newsockfd;
  unsigned int client_len;
  char *port = NULL;
  char *transport = "tcp";
  int i;
  int pid;
  int on = 1;
  int type;
  struct protoent *ppe;
  int rret = 0;
  char buffer[CHUNK_SIZE];

  i = 1;
  while (i < argc)
  {
    if (!strcmp(argv[i], "-p"))
    {
      i++;
      if (argv[i] == NULL)
      {
        fprintf(stderr, "Missing port\n");
        return 1;
      }
      port = argv[i];
      i++;
      continue;
    }
    else
    {
      fprintf(stderr, "Unknown option %s\n", argv[i]);
      return 1;
    }
  }

  if (port == NULL)
  {
    fprintf(stderr, "You need to specify a port\n");
    return 1;
  }

#ifdef DEBUG
  fprintf(stderr, "Starting server on port %s\n", port);
#endif

  bzero((char *) &server_addr, sizeof(server_addr));
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_family = AF_INET;
  if ((server_addr.sin_port = htons((u_short)atoi(port))) == 0)
  {
    fprintf(stderr, "Invalid port: %s\n", port);
    return 1;
  }

  type = SOCK_STREAM;
  if ((ppe = getprotobyname("TCP")) == 0)
  {
    fprintf(stderr, "ERROR: can't get \"%s\" protocol entry\n", transport);
    return 1;
  }

  sockfd = socket(PF_INET, type, ppe->p_proto);
  if (sockfd < 0)
  {
    fprintf(stderr, "ERROR: can't create socket: %s\n", strerror(errno));
    return 1;
  }

  on = 1;
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) == -1)
  {
    fprintf(stderr, "ERROR: can't set socket option: %s\n", strerror(errno));
    return 1;
  }

  if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
  {
    fprintf(stderr, "ERROR: can't bind socket: %s\n", strerror(errno));
    return 1;
  }

  if (type == SOCK_STREAM)
  {
    if (listen(sockfd, 5))
    {
      fprintf(stderr, "ERROR: listen on socket failed: %s\n", strerror(errno));
      return 1;
    }
  }

  (void) signal(SIGCHLD, reaper);

  while (1)
  {
    client_len = sizeof(client_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
    if (newsockfd < 0)
    {
      fprintf(stderr, "ERROR: accept on socket failed: %s\n", strerror(errno));
      return 1;
    }
    pid = fork();
    if (pid < 0)
    {
      fprintf(stderr, "ERROR: fork failed: %s\n", strerror(errno));
      return 1;
    }
    if (pid == 0)
    {
      /* Leak the rsp */
      register long long rsp asm ("rsp");
      printf("Here is the current stack pointer: %llx. You will need it.\n", rsp);
      close(0);
      dup(newsockfd);
      close(1);
      dup(newsockfd);
      close(newsockfd);
      return(manage_tcp_client());
    }
    close(newsockfd);
  }

  return 0; /* Never reached */
}
