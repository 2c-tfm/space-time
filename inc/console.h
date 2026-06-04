#ifndef CONSOLE_H
#define CONSOLE_H

#define MAX_LINE 1000
#define MAX_LOG 1000

typedef struct console {
	bool open;
	char cline[MAX_LINE];
	char log[MAX_LOG][MAX_LINE];
	time_t logtime[MAX_LOG];
	uint16_t log_it;
} console;

extern console cons;
void console_open(void);

#define LOG_SIZE 10
#define LOG_NUM (WIN_Y / 2) / (LOG_SIZE)
#define LOG_HORZ_MARGIN 1.5
#define LOG_VERT_MARGIN 35

#define CONS_INPUT_HEIGHT 30
#define CONS_INPUT_MARGIN 20
#define CONS_INPUT_TEXT_SIZE 10

#define CONS_HELP	"help - prints this message\n" \
			"fabric [on/off] - [enables/disables] the fabric of space\n" \
			"add_obj <name> <mass> <radius> <x> <y> <z> <outer_color> <inner_color> - adds an object to the current space\n" \
			"del_obj <name> - deletes the object from current space\n" \
			"cast_photon <ix> <iy> <iz> <hang> <vang> - cast photon from i* and direct's it using horizontal angle (azimuth) and vertical angle (elevation)\n" \
			"pause - pauses the simulation\n" \
			"resume - resumes the simulation\n" \
			"clear - clears message logs\n" \
			"exit - exits\n" \



void console_println(char *msg);


#endif
