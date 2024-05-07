#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 280

int foo(char *argv[])
{
  char buf[BUFLEN];
  strcpy(buf, argv[1]);
}

int main(int argc, char *argv[])
{
  if (argc != 2)
    {
      fprintf(stderr, "target0: argc != 2\n");
      exit(EXIT_FAILURE);
    }
  foo(argv);
  return 0;
}
