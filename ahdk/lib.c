// To be used, one day
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

int __aeabi_idivmod(int a, int b) {
	return divmod(a, b, 1);
}

void intToStr(char *buffer, int num) {
	int negative = 0;
	if (num < 0) {negative = 1; num *= -1;}

	int rem = 1;
	int length = 0;
	if (num < 10) {
		rem = 10;
	} else {
		int testLen = num;
		while (testLen != 0) {
			testLen = __aeabi_idiv(testLen, 10);
			rem *= 10;
			length++;
		}
	}

	// TODO: "length" to be used for
	// perfect char[] size

	int resultC = 0;
	if (negative) {
		resultC++;
		buffer[0] = '-';
	}

	while (rem != 1) {
		buffer[resultC] = (__aeabi_idivmod(num, rem) / (__aeabi_idiv(rem, 10))) + '0';
		rem = __aeabi_idiv(rem, 10);
		resultC++;
	}

	buffer[resultC] = '\0';
}
