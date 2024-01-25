int32_t main(int32_t argc, char** argv, char** envp) __noreturn
{
    int32_t var_14 = 0;
    void var_78;
    fgets(&var_78, 0x64, stdin);
    int32_t var_14_1 = 0;
    while (true)
    {
        int32_t ecx_1 = 0xffffffff;
        void* edi_1 = &var_78;
        while (ecx_1 != 0)
        {
            bool cond:0_1 = 0 != *edi_1;
            edi_1 = (edi_1 + 1);
            ecx_1 = (ecx_1 - 1);
            if ((!cond:0_1))
            {
                break;
            }
        }
        if (var_14_1 >= ((!ecx_1) - 1))
        {
            break;
        }
        if ((*(&var_78 + var_14_1) > 0x40 && *(&var_78 + var_14_1) <= 0x5a))
        {
            *(&var_78 + var_14_1) = (*(&var_78 + var_14_1) ^ 0x20);
        }
        var_14_1 = (var_14_1 + 1);
    }
    printf(&var_78);
    exit(0);
    /* no return */
}