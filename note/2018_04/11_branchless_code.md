# Branchless code

The modern processors have pipelining and branch prediction to accelerate the processing speed. However, it is common for processor to mispredict the correct branch. It can result in performance hit. There is an interesting code implementation called Branchless code. Branchless code aims to reduce any branch (IF, LOOP) from the code by using alternative operation.  

Since this topic is difficult for me to come up with my own code, I will follow the guide from the reference below:  

https://hbfs.wordpress.com/2008/08/05/branchless-equivalents-of-simple-functions/  

The article is really straightforward. We replace regular abs function with the help of sex (Sign EXtend) function which can be further derived from either shift operation or union (memory manipulation).  

    Regular abs
    inline unsigned int abs(int x) {
      return (x<0) ? -x : x;
    }

    abs using sex function
    inline unsigned int abs(int x) {
      return (x ^ sex(x)) - sex(x);
    }

    sex function from shift operation
    inline unsigned int sex(int x) {
      return x >> (CHAR_BIT*sizeof(int)-1);
    }

    sex function from memory manipulation
    inline int sex(int x) {
      union {
        // let us suppose long is twice as wide as int
        long w;

        // should be hi,lo on a big endian machine
        struct { int lo, hi; }
      } z = { .w=x };  
      return z.hi;
    }

The source code of my benchmark can be found in `_abs_benchmark.c`. The reason I put source code here is because there is many technical issues such as code format and optimization (depends on compiler)   

```
Running with 10^9 times of abs function.
Average from 10 rounds.

No optimized -O0
Average regular abs: 9.802
Average sex shift abs: 6.567
Average sex mem abs: 7.261

Level 1 optimized -O1
Average regular abs: 1.790
Average sex shift abs: 2.725
Average sex mem abs: 2.725

Level 3 optimized -O3
Average regular abs: 0.607
Average sex shift abs: 0.605
Average sex mem abs: 0.601
```

With no optimization, the result is pretty straightforward, regular abs (with CMP+JMP) is slower than abs using shift and mem. However, at optimization level 1, regular abs become faster !! So I peeked into the assembly code to see what's wrong there. Something isn't fit with our theory. And I saw the culprit:  

```
Dump of assembler code for function abs_reg:
   0x0000000100000e40 <+0>:	push   %rbp
   0x0000000100000e41 <+1>:	mov    %rsp,%rbp
   0x0000000100000e44 <+4>:	mov    %edi,%eax
   0x0000000100000e46 <+6>:	neg    %eax
   0x0000000100000e48 <+8>:	cmovl  %edi,%eax
   0x0000000100000e4b <+11>:	pop    %rbp
   0x0000000100000e4c <+12>:	retq   
   0x0000000100000e4d <+13>:	nopl   (%rax)
End of assembler dump.

Dump of assembler code for function abs_sex_shift:
   0x0000000100000e50 <+0>:	push   %rbp
   0x0000000100000e51 <+1>:	mov    %rsp,%rbp
   0x0000000100000e54 <+4>:	push   %rbx
   0x0000000100000e55 <+5>:	push   %rax
   0x0000000100000e56 <+6>:	mov    %edi,%ebx
   0x0000000100000e58 <+8>:	callq  0x100000e90 <sex_shift>
   0x0000000100000e5d <+13>:	xor    %eax,%ebx
   0x0000000100000e5f <+15>:	sub    %eax,%ebx
   0x0000000100000e61 <+17>:	mov    %ebx,%eax
   0x0000000100000e63 <+19>:	add    $0x8,%rsp
   0x0000000100000e67 <+23>:	pop    %rbx
   0x0000000100000e68 <+24>:	pop    %rbp
   0x0000000100000e69 <+25>:	retq   
   0x0000000100000e6a <+26>:	nopw   0x0(%rax,%rax,1)
End of assembler dump.
```

First, the compiler automatically optimized our regular abs into the branchless code !! Seconds, our `static inline` function doesn't get optimized by compiler. You can see that regular abs doesn't contain any function call while the sex abs contain a function call to sex_shift function. The inline function only works in optimization level 3.  

For most regular developers, I would suggest stopping here. In my opinion, ***Don't focus on complexed op code tricks, we should instead focus on macro performance such as scaling algorithm and loop and let the optimization be the job of compiler.*** Optimize level 3 seems to solve of our problem without having to peek into it for days.  

By the way, remember our not-working `inline` culprit ? It seems that we can improve our sex-abs performance further by changing `inline` token to `__attribute__((always_inline))` and compile again without optimization (-O0).  

```
Average regular abs: 8.800
Average sex shift abs: 3.025
Average sex mem abs: 4.119
```

So that's it. We intentionally ignore optimization from compiler (otherwise, this article would be pointless LOL) and write branchless code to improve our performance by more than twice !! It's fun to study but I suggest we should relying on compiler in most of our daily works to reduce time and error.

For reference:
```
Processor: 2.6 GHz Intel Core i5
$ gcc --version
Configured with: --prefix=/Library/Developer/CommandLineTools/usr --with-gxx-include-dir=/Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/usr/include/c++/4.2.1
Apple LLVM version 10.0.1 (clang-1001.0.46.3)
Target: x86_64-apple-darwin18.5.0
Thread model: posix
InstalledDir: /Library/Developer/CommandLineTools/usr/bin
```

Let's look a little bit more into assembly code after we have properly setup with inline. The assembly code are very straightforward. Both version has almost equal number of operation except that conditional jump is replaced with our operations. I can see that it's possible to optimize those code a bit more but, again, we should leave that job to compiler.

```
0x0000000100000b54 <+4>:	mov    %edi,-0x4(%rbp)
0x0000000100000b57 <+7>:	cmpl   $0x0,-0x4(%rbp)
0x0000000100000b5b <+11>:	jge    0x100000b6e <abs_reg+30>
0x0000000100000b61 <+17>:	xor    %eax,%eax
0x0000000100000b63 <+19>:	sub    -0x4(%rbp),%eax
0x0000000100000b66 <+22>:	mov    %eax,-0x8(%rbp)
0x0000000100000b69 <+25>:	jmpq   0x100000b74 <abs_reg+36>
0x0000000100000b6e <+30>:	mov    -0x4(%rbp),%eax
0x0000000100000b71 <+33>:	mov    %eax,-0x8(%rbp)
0x0000000100000b74 <+36>:	mov    -0x8(%rbp),%eax
   ```

```
0x0000000100000bc4 <+4>:	mov    %edi,-0xc(%rbp)
0x0000000100000bc7 <+7>:	mov    -0xc(%rbp),%edi
0x0000000100000bca <+10>:	mov    -0xc(%rbp),%eax
0x0000000100000bcd <+13>:	mov    %eax,-0x8(%rbp)
0x0000000100000bd0 <+16>:	mov    -0x8(%rbp),%eax
0x0000000100000bd3 <+19>:	sar    $0x1f,%eax
0x0000000100000bd6 <+22>:	xor    %eax,%edi
0x0000000100000bd8 <+24>:	mov    -0xc(%rbp),%eax
0x0000000100000bdb <+27>:	mov    %eax,-0x4(%rbp)
0x0000000100000bde <+30>:	mov    -0x4(%rbp),%eax
0x0000000100000be1 <+33>:	sar    $0x1f,%eax
0x0000000100000be4 <+36>:	sub    %eax,%edi
0x0000000100000be6 <+38>:	mov    %edi,%eax
   ```
