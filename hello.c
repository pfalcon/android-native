#include <stdio.h>
#include <stdlib.h>

int main()
{
  printf("Hello world!\n");
  return 0;
}

#ifdef NOT_USING_CRTBEGIN
extern "C" void _start(int argc, char *argv[])
{
  exit(main(argc, argv));
}
#endif
