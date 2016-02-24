#include <stdio.h>

void foo(int **const p)
{
    int j = 11;
    *p = &j;
    printf("foo: %d ", **p);
}

int main()
{
    int i = 10;
    int *p = &i;
    foo(&p);
    printf("main1: %d ", *p);
    printf("main2: %d ", *p);
}
