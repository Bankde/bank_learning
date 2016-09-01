#include <stdio.h>

#define isInput(argc) \
do { \
  if (argc > 1) { \
    printf("There is %d input.\n", (argc-1)); \
    break; \
  } \
  printf("There is no input.\n"); \
} while(0)

int main(int argc, char** argv) {
  isInput(argc);
}
