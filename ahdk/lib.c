int divmod(int a, int b, int o) {
	int di = 0;
	int re = 0;
	while (a != 0) {
		re++;
		di = 0;
		while (di != b) {
			if (a == 0) {
				break;
			}
			
			di++;
			a--;
		}
	}

	if (di == b) {
		di = 0;
	} else {
		re--;
	}
	
	if (o) {
		return di;
	}

	return re;
}

int __aeabi_idiv(int a, int b) {
	return divmod(a, b, 0);
}

int __aeabi_uidiv(int a, int b) {
	return divmod(a, b, 0);
}

int __aeabi_udivmod(int a, int b) {
	return divmod(a, b, 1);
}

int __aeabi_idivmod(int a, int b) {
	return divmod(a, b, 1);
}

int strlen(char *buffer) {
	int a = 0;
	while (*buffer != 0) {
		buffer++;
		a++;
	}

	return a;
}

void *memcpy(void* dest, const void* src, int count) {
	char* dst8 = (char*)dest;
	char* src8 = (char*)src;
	while (count--) {
		*dst8++ = *src8++;
	}
	
	return dest;
}

void *memset(void *dest, int val, int len) {
	unsigned char *ptr = dest;
	while (len-- > 0) {
		*ptr++ = val;
	}
	
	return dest;
}
