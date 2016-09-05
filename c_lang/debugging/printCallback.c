#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

struct test_cb {
  int id;
  void (*callback)();
};

int f1(struct test_cb *obj) {
  printf("This is %s executing callback\n", __FUNCTION__);
  backtrace_symbols_fd(&obj->callback, 1, 1);
  (*obj->callback)();
  return 0;
}

void *function_cb() {
  printf("This is a callback in %s\n", __FUNCTION__);
}

int main() {
  struct test_cb *newObj = (struct test_cb*)malloc(sizeof(struct test_cb));
  newObj->id = 1;
  newObj->callback = function_cb;
  f1(newObj);
  return 0;
}
