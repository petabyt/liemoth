void _start() {
	int (*mkdir)(char *string) = (int (*)(char *string))AMB_MKDIR + 1;
	mkdir("d:/asdasdasd");
}