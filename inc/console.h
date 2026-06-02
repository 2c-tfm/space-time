#ifndef CONSOLE_H
#define CONSOLE_H

#define MAX_LINE 1000
#define MAX_LOG 1000

typedef struct console {
	bool open;
	char cline[MAX_LINE];
	char log[MAX_LOG][MAX_LINE];
	uint16_t log_it;
} console;

extern console cons;
void console_open(void);

#define LOG_SIZE 14
#define LOG_NUM (WIN_Y / 2) / (LOG_SIZE)
#define LOG_HORZ_MARGIN 1.5
#define LOG_VERT_MARGIN 35

#define CONS_INPUT_HEIGHT 40
#define CONS_INPUT_MARGIN 20
#define CONS_INPUT_TEXT_SIZE 20

#endif
