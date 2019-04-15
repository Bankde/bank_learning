#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define COUNT 1000*1000*1000*1
#define TEST_COUNT 10 

__attribute__((always_inline)) unsigned int abs_reg(int x) {
  return (x < 0) ? -x: x;
}

__attribute__((always_inline)) unsigned int sex_shift(int x) {
  return x >> (__CHAR_BIT__*sizeof(int)-1);
}

__attribute__((always_inline)) int sex_mem(int x) {
  union {
    long w;
    struct { int lo, hi; };
  } z;
  z.w = x;
  return z.hi;
}

__attribute__((always_inline)) unsigned int abs_sex_shift(int x) {
  return (x ^ sex_shift(x)) - sex_shift(x);
}

__attribute__((always_inline)) unsigned int abs_sex_mem(int x) {
  return (x ^ sex_mem(x)) - sex_mem(x);
}

double getCurrentTime() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double time_in_mill = (tv.tv_sec)*1000 + (tv.tv_usec)/1000;
  return time_in_mill;
}

int main() {
  int *buffer;
  volatile int result;

  buffer = malloc(COUNT*sizeof(int));
  srand(getCurrentTime());
  for (long i=0; i<COUNT; i++) buffer[i] = rand()-(RAND_MAX/2);

  double sum_reg, sum_shift, sum_mem;
  double start, end;

  for (int j=0; j<TEST_COUNT; j++) {
    start = getCurrentTime();
    for (long i=0; i<COUNT; i++) result = abs_reg(buffer[i]);
    end = getCurrentTime();
    sum_reg += (end-start);

    start = getCurrentTime();
    for (long i=0; i<COUNT; i++) result = abs_sex_shift(buffer[i]);
    end = getCurrentTime();
    sum_shift += (end-start);

    start = getCurrentTime();
    for (long i=0; i<COUNT; i++) result = abs_sex_mem(buffer[i]);
    end = getCurrentTime();
    sum_mem += (end-start);

    printf("Done 1 round\n");
  }

  printf("Average regular abs: %.03f\n", (sum_reg/TEST_COUNT)/1000);
  printf("Average sex shift abs: %.03f\n", (sum_shift/TEST_COUNT)/1000);
  printf("Average sex mem abs: %.03f\n", (sum_mem/TEST_COUNT)/1000);

  return 0;
}
