#include "header.h"

int ahdkInfo() {
	line = 0;
	ambsh_sprintf(buffer, "AHDK Menu: Model: %s", P_NAME);
	print(buffer);
	print("Press select button to exit.");
	drawImage(140, 50, 150, 150, "d:/ahdk/logo.bin");
	waitButton(P_SELBTN);
	return 0;
}

int resumeToOS() {
	clearScreen();
	countDown(2);
	return 1;
}

void writeAmbsh(char *buffer) {
	FILE *file = ambsh_fopen("d:/ahdk/a.ash", "w");
	ambsh_fwrite(buffer, 1, strlen(buffer), file);
	ambsh_fclose(file);
}

int optionSetting() {
	
}

struct MenuItem mainMenu[] = {
	{"Resume to OS", resumeToOS, ACTION},
	{"Option setting", optionSetting, SELECT},
	{"AHDK Info", ahdkInfo, ACTION},
	{0}
};
