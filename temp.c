#include <stdio.h>

#define UART 0x60

int
main (int argc, char *argv[])
{

  int x = 0xff;

  x &= ~(1 << 3);
  printf("\n%x\n\n", x);

  return 0;
}
