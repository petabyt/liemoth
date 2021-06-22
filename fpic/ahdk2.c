int farts() {
	int (*mkdir)(char *string) = (int (*)(char *string))AMB_MKDIR + 1;
	mkdir("d:/fat");
}