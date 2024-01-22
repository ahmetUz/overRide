int32_t main(int32_t argc, char** argv, char** envp)
{
    pid_t eax = fork();
    void var_a0;
    __builtin_memset(&var_a0, 0, 0x80);
    int32_t var_18 = 0;
    int32_t var_a4 = 0;
    if (eax == 0)
    {
        prctl(1, 1);
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        puts("Give me some shellcode, k");
        gets(&var_a0);
    }
    else
    {
        while (true)
        {
            wait(&var_a4);
            if (((var_a4 & 0x7f) != 0 && (((var_a4 & 0x7f) + 1) >> 1) <= 0))
            {
                if (ptrace(PTRACE_PEEKUSER, eax, 0x2c, 0) == 0xb)
                {
                    puts("no exec() for you");
                    kill(eax, 9);
                    break;
                }
                continue;
            }
            puts("child is exiting...");
            break;
        }
    }
    return 0;
}