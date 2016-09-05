#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

int f1() {
  printf("Check f1\n");
  void* funcPtrs = (void*)calloc(sizeof(f1)*10,1);
  int depth = backtrace(funcPtrs, 10);
  backtrace_symbols_fd(funcPtrs, depth-1, 1);
  return 0;
}

int f2() {
  printf("Check f2\n");
  f1();
  return 0;
}

int main() {
  printf("Main\n");
  f2();
  return 0;
}
