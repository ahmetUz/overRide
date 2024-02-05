int64_t log_wrapper(FILE* arg1, char* arg2, char* arg3)
{
    void* fsbase;
    int64_t rax = *(fsbase + 0x28);
    void var_118;
    strcpy(&var_118, arg2);
    int64_t rcx = -1;
    void* rdi_1 = &var_118;
    while (rcx != 0)
    {
        bool cond:0_1 = 0 != *rdi_1;
        rdi_1 = (rdi_1 + 1);
        rcx = (rcx - 1);
        if ((!cond:0_1))
        {
            break;
        }
    }
    int64_t rcx_1 = -1;
    void* rdi_2 = &var_118;
    while (rcx_1 != 0)
    {
        bool cond:1_1 = 0 != *rdi_2;
        rdi_2 = (rdi_2 + 1);
        rcx_1 = (rcx_1 - 1);
        if ((!cond:1_1))
        {
            break;
        }
    }
    snprintf((&var_118 + ((!rcx_1) - 1)), (0xfe - ((!rcx) - 1)), arg3);
    *(&var_118 + strcspn(&var_118, &data_400d4c)) = 0;
    fprintf(arg1, "LOG: %s\n", &var_118, "LOG: %s\n");
    int64_t rax_11 = (rax ^ *(fsbase + 0x28));
    if (rax_11 == 0)
    {
        return rax_11;
    }
    __stack_chk_fail();
    /* no return */
}

int32_t main(int32_t argc, char** argv, char** envp)
{
    void* fsbase;
    int64_t rax = *(fsbase + 0x28);
    char var_79 = 0xff;
    int32_t var_80 = 0xffffffff;
    if (argc != 2)
    {
        printf("Usage: %s filename\n", *argv);
    }
    FILE* rax_4 = fopen("./backups/.log", &data_400d6b);
    if (rax_4 == 0)
    {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
        exit(1);
        /* no return */
    }
    log_wrapper(rax_4, "Starting back up: ", argv[1]);
    FILE* rax_12 = fopen(argv[1], &data_400da9);
    if (rax_12 == 0)
    {
        printf("ERROR: Failed to open %s\n", argv[1]);
        exit(1);
        /* no return */
    }
    int64_t var_78;
    __builtin_strncpy(var_78, "./backups/", 0xb);
    int64_t rcx = -1;
    int64_t* rdi_2 = &var_78;
    while (rcx != 0)
    {
        bool cond:0_1 = 0 != *rdi_2;
        rdi_2 = (rdi_2 + 1);
        rcx = (rcx - 1);
        if ((!cond:0_1))
        {
            break;
        }
    }
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
    log_wrapper(rax_4, "Finished back up ", argv[1]);
    fclose(rax_12);
    close(rax_22);
    if (rax == *(fsbase + 0x28))
    {
        return 0;
    }
    __stack_chk_fail();
    /* no return */
}