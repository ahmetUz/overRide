int __cdecl decrypt(char a1)
{
  unsigned int i; // [esp+20h] [ebp-28h]
  unsigned int v3; // [esp+24h] [ebp-24h]
  char v4[29]; // [esp+2Bh] [ebp-1Dh] BYREF

  *(_DWORD *)&v4[17] = __readgsdword(0x14u);
  strcpy(v4, "Q}|u`sfg~sf{}|a3");
  v3 = strlen(v4);
  for ( i = 0; i < v3; ++i )
    v4[i] ^= a1;
  if ( !strcmp(v4, "Congratulations!") )
    return system("/bin/sh");
  else
    return puts("\nInvalid Password");
}
// 8048746: positive sp value 4 has been found

//----- (08048747) --------------------------------------------------------
int __cdecl test(int a1, int a2)
{
  int result; // eax
  char v3; // al

  switch ( a2 - a1 )
  {
    case 1:
	 result = decrypt(a2 - a1);
    case 2:
	 result = decrypt(a2 - a1);
    case 3:
	 result = decrypt(a2 - a1);
    case 4:
	 result = decrypt(a2 - a1);
    case 5:
	 result = decrypt(a2 - a1);
    case 6:
	 result = decrypt(a2 - a1);
    case 7:
	 result = decrypt(a2 - a1);
    case 8:
	 result = decrypt(a2 - a1);
    case 9:
	 result = decrypt(a2 - a1);
    case 16:
	 result = decrypt(a2 - a1);
    case 17:
	 result = decrypt(a2 - a1);
    case 18:
	 result = decrypt(a2 - a1);
    case 19:
	 result = decrypt(a2 - a1);
    case 20:
	 result = decrypt(a2 - a1);
    case 21:
      result = decrypt(a2 - a1);
      break;
    default:
      v3 = rand();
      result = decrypt(v3);
      break;
  }
  return result;
}

//----- (0804885A) --------------------------------------------------------
int __cdecl main(int argc, const char **argv, const char **envp)
{
  unsigned int v3; // eax
  int savedregs; // [esp+20h] [ebp+0h] BYREF

  v3 = time(0);
  srand(v3);
  puts("***********************************");
  puts("*\t\tlevel03\t\t**");
  puts("***********************************");
  printf("Password:");
  __isoc99_scanf("%d", &savedregs);
  test(savedregs, 322424845);
  return 0;
}