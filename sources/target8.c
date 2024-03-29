#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int foo(char *argv[])
{
  char buf[344];
  strcpy(buf, argv[1]);
}

int main(int argc, char *argv[])
{
  if (argc != 2)
    {
      fprintf(stderr, "target8: argc != 2\n");
      exit(EXIT_FAILURE);
    }
  foo(argv);
  return 0;
}

