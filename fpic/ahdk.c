void printf(int *env, char *fmt, ...);

char *name = "John Doe";

void _start(int *env, long addr) {
	char a;
	printf(env, "Allocated: 0x%x\n", addr);
	printf(env, "Stack 0x%x\n", &a);
	printf(env, "Global ?? %s\n", name);
}
