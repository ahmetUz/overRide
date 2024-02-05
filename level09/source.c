struct	s_message
{
	char	message[140];
	char	username[40];
	int		len;
}   t_message;

long long secret_backdoor()
{
    char v0;  // [bp-0x88]

    fgets(&v0, 128, stdin);
    return system(&v0);
}


void set_msg(t_message *a0)
{
    char v1;  // [bp-0x408], Other Possible Types: void*
    unsigned long long *v3;  // rdi
    unsigned long long v4;  // rcx
    unsigned long v5;  // d

    v3 = &v1;
    for (v4 = 128; v4; v3 = &v3[v5])
    {
        v4 -= 1;
        v1 = 0;
    }
    puts(">: Msg @Unix-Dude");
    printf(">>: ");
    fgets(&v1, 0x400, stdin);
    strncpy(a0->message, &v1, a0->len);
    return;
}

extern char stdin;

void set_username(t_message *a0)
{
    unsigned long v0;  // [bp-0xa0]
    void* v1;  // [bp-0x98], Other Possible Types: char
    unsigned int v2;  // [bp-0xc]
    void* v4;  // rdi
    unsigned long long v5;  // rcx
    unsigned long v6;  // d

    v4 = &v1;
    for (v5 = 16; v5; v4 += v6 * 8)
    {
        v5 -= 1;
        v1 = 0;
    }
    puts(">: Enter your username");
    printf(">>: ");
    fgets(&v1, 128, stdin);
    for (v2 = 0; v2 <= 40 && (&v1)[v2]; v2 += 1)
    {
        a0->username[v2] = (&v1)[v2];
    }
    printf(">: Welcome, %s", a0->username);
    return;
}

void handle_msg()
{
    t_message v0;
    void* v1;  // [bp-0x3c]
    void* v2;  // [bp-0x34]
    void* v3;  // [bp-0x2c]
    void* v4;  // [bp-0x24]
    void* v5;  // [bp-0x1c]
    unsigned int v6;  // [bp-0x14]

    v1 = 0;
    v2 = 0;
    v3 = 0;
    v4 = 0;
    v5 = 0;
    v6 = 140;
    set_username(&v0);
    set_msg(&v0);
    puts(">: Msg sent!");
    return;
}

int main()
{
    puts("--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337        |\n--------------------------------------------");
    handle_msg();
    return 0;
}