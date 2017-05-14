#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://sourceware.org/glibc/wiki/MallocInternals

int main() {
  // also meta 0x21
  char* one = malloc(1);
  // meta 0x21 (2 of 16 bytes, including this meta itself)
  char* a = malloc(20);
  char* b = malloc(6);
  char* c = malloc(7);
  char* d = malloc(8);
  char* e = malloc(12);
  char* f = malloc(16);
  char* g = malloc(24);
  // meta 0x31 (because 25 + 8(meta) > 2x16, it expands to 3x16)
  char* h = malloc(25);
  char* i = malloc(40);
  // meta 0x41
  char* j = malloc(41);
  memset(one,1,1);
  strcpy(a,"aaaaaaaaaaaaaaaaaaa");
  strcpy(b,"bbbb");
  strcpy(c,"cccc");
  strcpy(d,"dddd");
  strcpy(e,"eeee");
  strcpy(f,"ffff");
  strcpy(g,"gggg");
  strcpy(h,"hhhh");
  strcpy(i,"iiii");
  strcpy(j,"jjjj");
  for (int i=0; i<10; i++) {
    printf("break %d\n", i);
    sleep(1);
  }
  // remove data in 'b'
  free(b);
  // replace data in 'c' with address of before 'b' (0x8 before 'b')
  free(c);
  // replace data in 'd' with address of before 'c' (0x8 before 'c')
  free(d);
  // same as above... before 'd'
  free(e);
  // this malloc at previous 'e' address
  // leave address to before 'e' as it is, perhaps already been read/save to somewhere else ?
  char* z = malloc(10);
  strcpy(z,"zzzz");
  // this malloc at previous 'd' address (apparently, fastbin works like stack)
  char* y = malloc(10);
  strcpy(y,"yyyy");
  for (int i=0; i<10; i++) {
    printf("break %d\n", i);
    sleep(1);
  }
  printf("Done\n");
  return 0;
}

