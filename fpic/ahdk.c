int malloc(int id, int size, void *address);

void _start() {
	int *a;
	malloc(1, 1000, &a);
}
