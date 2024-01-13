int main(void) {
	int	mdp[4];
	puts("***********************************");
	puts("* \t     -Level00 -\t\t  *");
	puts("***********************************");
	printf("Password:");
	__isoc99_scanf("%d");
	if (mdp[0] == 0x149c) {
		puts("\nAuthenticated!");
		system("/bin/sh");
	} else
		puts("\nInvalid Password!");
}