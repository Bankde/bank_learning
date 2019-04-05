# Signed VS Unsigned right shift

This topic focuses on different of right shift to signed and unsigned integer which are mainly how c,c++ compiler choose between logical shift and arithmetic shift.  

> a "logical" right shift by 1 bit shifts all the bits to the right and fills in the leftmost bit with a 0. An "arithmetic" shift leaves the original value in the leftmost bit. The difference becomes important when dealing with negative numbers.  

There is a very good explanation here:  

https://stackoverflow.com/questions/7622/are-the-shift-operators-arithmetic-or-logical-in-c

> When shifting left, there is no difference between arithmetic and logical shift. When shifting right, the type of shift depends on the type of the value being shifted.  

So I tried a simple program on OSX 10.13.3 and compiled Apple LLVM version 9.0.0 (clang-900.0.39.2):  

    signed.c - Arithmetic Shift               unsigned.c - Logical Shift
    int rotate(int x, int count) {            int rotate(int x, int count) {
        return (x >> count);                      return (int)((unsigned int)x >> count);
    }                                         }

    $ ./signed.o -243 3                       $ ./rotate_unsign.o -243 3
    11111111111111111111111100001101          11111111111111111111111100001101
    11111111111111111111111111100001          00011111111111111111111111100001

This is however, as explained in stackoverflow above, implementation-defined. So developer MUST test or check the compiler specification or NOT rely on it at all.  

While it is much pretty clear already, let's peek a bit into assembly to see how compiler handles these functions differently.  

    signed.c                                                unsigned.c
    0x0000000100000ec0 <+0>:  push   %rbp                   0x0000000100000ec0 <+0>:  push   %rbp
    0x0000000100000ec1 <+1>:  mov    %rsp,%rbp              0x0000000100000ec1 <+1>:  mov    %rsp,%rbp
    0x0000000100000ec4 <+4>:  mov    %edi,-0x4(%rbp)        0x0000000100000ec4 <+4>:  mov    %edi,-0x4(%rbp)
    0x0000000100000ec7 <+7>:  mov    %esi,-0x8(%rbp)        0x0000000100000ec7 <+7>:  mov    %esi,-0x8(%rbp)
    0x0000000100000eca <+10>: mov    -0x4(%rbp),%esi        0x0000000100000eca <+10>: mov    -0x4(%rbp),%esi
    0x0000000100000ecd <+13>: mov    -0x8(%rbp),%ecx        0x0000000100000ecd <+13>: mov    -0x8(%rbp),%ecx
    0x0000000100000ed0 <+16>: sar    %cl,%esi               0x0000000100000ed0 <+16>: shr    %cl,%esi
    0x0000000100000ed2 <+18>: mov    %esi,%eax              0x0000000100000ed2 <+18>: mov    %esi,%eax
    0x0000000100000ed4 <+20>: pop    %rbp                   0x0000000100000ed4 <+20>: pop    %rbp
    0x0000000100000ed5 <+21>: retq                          0x0000000100000ed5 <+21>: retq

It is not hard to compare here. We can see that "sar" is Shift Arithmetic Right and "shr" is Shift Logical Right. The compiler merely picks the assembly function based on the current variable type.  
