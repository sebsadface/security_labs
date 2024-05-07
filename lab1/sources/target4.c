#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 96

int foo(char *arg, short arglen)
{
  int maxlen = BUFLEN;
  char buf[BUFLEN];

  if (arglen < maxlen)
    memcpy(buf, arg, strlen(arg));

  return 0;
}

int main(int argc, char *argv[])
{
  if (argc != 2)
    {
      fprintf(stderr, "target4: argc != 2\n");
      exit(EXIT_FAILURE);
    }

  foo(argv[1], strlen(argv[1]));

  return 0;
}
