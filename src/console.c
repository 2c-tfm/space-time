#include <space_time.h>

console cons = {
	.open = false,
	.log_it = 0,
};

static void console_print_logs(void) {
	uint16_t it_log = 0;

	if (((int16_t) cons.log_it) - LOG_NUM > 0)
		it_log = cons.log_it - LOG_NUM;
	while (it_log < cons.log_it){
		DrawText(cons.log[it_log], LOG_VERT_MARGIN, LOG_SIZE * ((it_log + 1) * LOG_HORZ_MARGIN),
				LOG_SIZE,  BLACK);
		it_log++;
	}
}


static bool console_input_box(void){
	char *cons_inp;
	uint16_t pkey;
	uint32_t line_it = 0;

	DrawRectangle(0, WIN_Y / 2, WIN_X, CONS_INPUT_HEIGHT , DARKGRAY);
	cons_inp = "> ";
	if (time(0) % 2 != 0 && cons.cline[0] == '\0')
		cons_inp = "> _";
	
	DrawText(cons_inp, 0 + CONS_INPUT_MARGIN, (WIN_Y / 2)  + 
			(CONS_INPUT_HEIGHT / 2 - (CONS_INPUT_HEIGHT / 8)),
			CONS_INPUT_TEXT_SIZE,  BLACK);

	
	if (pkey == 0)
		return (false);
	printf("pkey [%c] %s\n", pkey, cons.cline);
	if (pkey == KEY_ENTER)
		return (true);
	if (pkey == KEY_BACKSPACE && ((int32_t) line_it) - 1 > 0)
		cons.cline[line_it--] = '\0';
	else 
		cons.cline[line_it++] = pkey;

	return (false);
}

void console_open(void){
	DrawRectangle(0, 0, WIN_X, WIN_Y / 2, Fade(GRAY, 1.6f));
	console_print_logs();
	console_input_box();

}
