#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

#include "kbhit.h"

static struct termios oldt, newt;
static int old_stdin_fd;


int kbhit_init()
{
	// config terminal parameters
	tcgetattr(0, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	// config stdin fd 
	old_stdin_fd = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, old_stdin_fd | O_NONBLOCK);

	return 0;
}

int kbhit_uninit()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, old_stdin_fd);

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