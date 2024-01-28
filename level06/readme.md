In this level, we need to enter a value for the identifier and a serial number.
```c
 puts("***********************************");
  puts("*\t\tlevel06\t\t  *");
  puts("***********************************");
  printf("-> Enter Login: ");
  fgets(local_34,0x20,stdin);
  puts("***********************************");
  puts("***** NEW ACCOUNT DETECTED ********");
  puts("***********************************");
  printf("-> Enter Serial: ");
  __isoc99_scanf();
```

Afterward, these two values will be passed to an authentication function that will authenticate the user.

```c
int auth(char *param_1,uint param_2)
```

If this function returns 0, system("/bin/sh") is executed.

```c
iVar1 = auth();
if (iVar1 == 0) {
	puts("Authenticated!");
	system("/bin/sh");
}
```
So, we need to ensure that auth() returns 0, but how ?

To achieve this, this condition must return true.
```c
if (param_2 == local_14) {
	return(0);
}
```
Here, param_2 is the serial that was previously entered.

So we can use GDB to find the location of local_14 and then display its content

```asm
0x08048863 <+283>:   mov    0xc(%ebp),%eax
0x08048866 <+286>:   cmp    -0x10(%ebp),%eax  <----0x10(%ebp)
0x08048869 <+289>:   je     0x8048872 <auth+298>
```
We need to display the content of -0x10(%ebp).

But we have a problem, as can be seen below; if the process is being debugged, the program displays an error message and stops.

```c
lVar3 = ptrace(PTRACE_TRACEME);
if (lVar3 == -1) {
	puts("\x1b[32m.---------------------------.");
	puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
	puts("\x1b[32m\'---------------------------\'");
	return(1);
}
```

```asm
0x080487b5 <+109>:   call   0x80485f0 <ptrace@plt>
=> 0x080487ba <+114>:   cmp    $0xffffffff,%eax
0x080487bd <+117>:   jne    0x80487ed <auth+165>
```
So, to prevent this issue, we can set the eax to 1.

```
Program received signal SIGINT, Interrupt.
0x080487ba in auth ()
(gdb) set $eax=1
```

we retrieve the address of $ebp - 0x10, and then we display its content.

```
(gdb) x/x $ebp - 0x10
0xffffd6a8:     0x005f1ec5
```

```
(gdb) print 0x005f1ec5
$2 = 6233797
```

```
level06@OverRide:~$ ./level06
***********************************
*               level06           *
***********************************
-> Enter Login: aaaabbbb
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6233797
Authenticated!
$ whoami
level07
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```