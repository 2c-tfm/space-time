#ifndef CONSOLE_H
#define CONSOLE_H

#define MAX_LINE 1000
#define MAX_CLOG 1000

typedef struct console {
	bool open;
	char cline[MAX_LINE];
	char clog[MAX_CLOG][MAX_LINE];
	uint16_t clog_it;
} console;

extern console cons;
void console_open(void);

#endif
