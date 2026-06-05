#include <stdio.h>
#include <termios.h>
#include <fcntl.h>

#include "kbhit.h"

static struct termios oldt, newt;
static int old_stdin_fd, new_stdin_fd;


int kbhit_init()
{
	// config terminal parameters
	tcgetattr(0, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &newt);

	// config stdin fd 
	old_stdin_fd = fcntl(0, F_GETFL, 0);
	fcntl(0, F_SETFL, old_stdin_fd | O_NONBLOCK);

	return 0;
}

int kbhit_uninit()
{
	tcsetattr(0, TCSANOW, &oldt);
	fcntl(0, F_SETFL, old_stdin_fd);

	return 0;
}

int kbhit(void)
{
	int ch;

	ch = getchar();

	if(ch != EOF) {
		ungetc(ch, stdin);
		return -1;
	}

	return 0;
}