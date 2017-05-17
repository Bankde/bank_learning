#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char* s = malloc(20);
  printf("Enter your name: ");
  scanf("%s", s);
  printf("%s\n", s);
  printf("Take a break\n");
  for (int i=0; i<100; i++) {
    printf("hello %s %d\n", s, i);
    sleep(1);
  }
  printf("Done %s\n", s);
  printf("Done\n");
  return 0;
}

