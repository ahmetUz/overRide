int32_t main(int32_t argc, char** argv, char** envp)
{
    int32_t var_11c = argc;
    char** var_128 = argv;
    void var_78;
    __builtin_memset(&var_78, 0, 0x60);
    int32_t* rdi;
    *rdi = 0;
    void var_a8;
    __builtin_memset(&var_a8, 0, 0x28);
    char* rdi_1;
    *rdi_1 = 0;
    void var_118;
    __builtin_memset(&var_118, 0, 0x60);
    int32_t* rdi_2;
    *rdi_2 = 0;
    int64_t var_10 = 0;
    int32_t var_14 = 0;
    FILE* rax = fopen("/home/users/level03/.pass", &data_400bb0);
    if (rax == 0)
    {
        fwrite("ERROR: failed to open password f…", 1, 0x24, stderr);
        exit(1);
        /* no return */
    }
    int32_t rax_1 = fread(&var_a8, 1, 0x29, rax);
    *(&var_a8 + strcspn(&var_a8, &data_400bf5)) = 0;
    if (rax_1 != 0x29)
    {
        fwrite("ERROR: failed to read password f…", 1, 0x24, stderr);
        fwrite("ERROR: failed to read password f…", 1, 0x24, stderr);
        exit(1);
        /* no return */
    }
    fclose(rax);
    puts("===== [ Secure Access System v1.…");
    puts("/*******************************…");
    puts("| You must login to access this …");
    puts("\*******************************…");
    printf("--[ Username: ");
    fgets(&var_78, 0x64, stdin);
    *(&var_78 + strcspn(&var_78, &data_400bf5)) = 0;
    printf("--[ Password: ");
    fgets(&var_118, 0x64, stdin);
    *(&var_118 + strcspn(&var_118, &data_400bf5)) = 0;
    puts("********************************…");
    if (strncmp(&var_a8, &var_118, 0x29) != 0)
    {
        printf(&var_78);
        puts(" does not have access!");
        exit(1);
        /* no return */
    }
    printf("Greetings, %s!\n", &var_78, &var_78);
    system("/bin/sh");
    return 0;
}