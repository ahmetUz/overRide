For this level, observe that there is a condition checking if the password (mdp) is equal to 0x149c (5276).
If the condition return true system("/bin/sh") is run and we WIN !

```c
if (mdp[0] == 0x149c) {
	puts("\nAuthenticated!");
	system("/bin/sh");
}
```

Additionally, we can se that there is an scanf who change  password (mdp).

```c
int mdp[4];
printf("Password:");
__isoc99_scanf("%d");
```

hence through keyboard input

```bash
level00@OverRide:~$ ./level00
***********************************
*            -Level00 -           *
***********************************
Password:5276
Authenticated!
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```
