This level takes a number as an argument.

```c
	printf("Password:");
 	 __isoc99_scanf("%d", &savedregs);
```

then this number is sent as an argument to another function along with another number (322424845).

```c
test(savedregs, 322424845);
```

This test function will call another function decrypt, which will take as an argument the result of subtracting 322424845 from the entered number.

```c
decrypt(a2 - a1);
```

Everything happens in this function. We have a string containing 'Q}|usfg~sf{}|a3,' and this string will be modified using the argument. For each character, the XOR operation is applied with the argument.

Then a comparison is applied to check if the modified string is equal to 'Congratulations!' If that's the case, a /bin/sh is executed.

```c
if ( !strcmp(v4, "Congratulations!") )
    return system("/bin/sh");
```

So the objective is to find the decryption key for the string 'Q}|usfg~sf{}|a3'.
Let's take the first letter Q; we want to make it equal to C. Q = 01010001, and C = 01000011. Let's perform a simple operation to find the key.

```
Q = 01010001 (81)
	00010010 (18)
	--------
C = 01000011 (67)
```
the key is 18 PERFECT! Now, we need to ensure that the subtraction in the function test results in 18 -> 322424845 - 18 = 322424827.

```
level03@OverRide:~$ ./level03
***********************************
*               level03         **
***********************************
Password:322424827
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```