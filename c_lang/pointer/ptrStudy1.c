#include <stdio.h>

// The answer is foo: 11 main1: 11 main2: 0
// Explaination:
// 1. address p being throw into foo
// 2. change the value of p (pointer value) from address of i=10 to to address of j=11
// 3. function foo is done. foo stack is popped. address of j=11 is now invalid but still exist (because c never clear anything)
// 4. j=11 is still invalid-ally exist, p get value from j=11, push into $rax, and call printf function.
// 5. the call printf function push sth into stack, overwriting the j=11, then done, pop everything out.
// 6. j=11 is now gone, second call printf result becomes undefined (usually 0 I guess)

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
