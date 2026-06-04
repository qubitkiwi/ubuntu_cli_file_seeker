#include "common.h"
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
// #include <unistd.h>

int kbhit(void)
{
	struct termios oldt, newt;
	int ch, oldf;

	tcgetattr(0, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &newt);
	oldf = fcntl(0, F_GETFL, 0);
	fcntl(0, F_SETFL, oldf | O_NONBLOCK);
	ch = getchar();

	tcsetattr(0, TCSANOW, &oldt);
	fcntl(0, F_SETFL, oldf);

	if(ch != EOF) {
		ungetc(ch, stdin);
		return -1;
	}

	return 0;
}