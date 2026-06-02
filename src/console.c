#include <space_time.h>

console cons = {
	.open = false,
	.log_it = 0,
};

uint32_t line_it = 0;

static void time_t_to_strtime(char *buff, time_t time, uint32_t bsize) {
	struct tm *tinfo = localtime(&time);
	strftime(buff, bsize, "%H:%M:%S", tinfo);
}

static void console_clear(void) {
	memset(&cons, 0, sizeof(console));
	cons.open = true;
	line_it = 0;
}

static void console_print_logs(void) {
	uint16_t it_log = 0;
	char timebuff[64];

	DrawRectangle(0, 0, WIN_X, WIN_Y / 2, BLACK);

	if (((int16_t) cons.log_it) - LOG_NUM > 0)
		it_log = cons.log_it - LOG_NUM;
	while (it_log < cons.log_it){
		if (cons.logtime[it_log] != 0){
			time_t_to_strtime(timebuff, cons.logtime[it_log], 64);
			DrawText(timebuff, LOG_VERT_MARGIN, LOG_SIZE * ((it_log + 1) * LOG_HORZ_MARGIN),
					LOG_SIZE,  LIGHTGRAY);
		}
		DrawText(cons.log[it_log], (LOG_VERT_MARGIN * 2) + 10, LOG_SIZE * ((it_log + 1) * LOG_HORZ_MARGIN),
				LOG_SIZE,  LIGHTGRAY);

		memset(timebuff, 0, 64);
		it_log++;
	}
}

static bool console_input_box(void){
	char *cons_inp;
	uint16_t pkey = GetKeyPressed();
	uint16_t ckey = GetCharPressed();

	DrawRectangle(0, WIN_Y / 2, WIN_X, CONS_INPUT_HEIGHT , Fade(LIGHTGRAY, 0.4f));

	cons_inp = ">> ";
	if (time(0) % 2 != 0 && cons.cline[0] == '\0')
		cons_inp = ">> _";
	
	DrawText(cons_inp, 0 + CONS_INPUT_MARGIN, (WIN_Y / 2)  + 
			(CONS_INPUT_HEIGHT / 2 - (CONS_INPUT_HEIGHT / 8)),
			CONS_INPUT_TEXT_SIZE,  BLACK);

	if (cons.cline[0] != '\0')
		DrawText(cons.cline, 0 + CONS_INPUT_MARGIN + CONS_INPUT_TEXT_SIZE, (WIN_Y / 2)  + 
				(CONS_INPUT_HEIGHT / 2 - (CONS_INPUT_HEIGHT / 8)),
				CONS_INPUT_TEXT_SIZE,  BLACK);
	
	if (pkey == 0)
		return (false);
	if (pkey == KEY_ENTER || line_it >= MAX_LINE){
		cons.cline[line_it] = '\0';
		return (true);
	}
	if (pkey == KEY_BACKSPACE && ((int32_t) line_it - 1) > -1)
		cons.cline[--line_it] = '\0';
	else if (ckey != '\0')
		cons.cline[line_it++] = ckey;
	return (false);
}

static void console_println(char *msg){
	char *nl_ptr = msg;
	bool firstnl_line = true;

	if (strchr(msg, '\n') == NULL){
		cons.logtime[cons.log_it] = time(0);
		strcpy(cons.log[cons.log_it], msg);
		cons.log_it++;
	} else {
		// we got new lines 
		while (strchr(nl_ptr, '\n') != NULL) {
			if (firstnl_line == true){
				firstnl_line = false;
				cons.logtime[cons.log_it] = time(0);
			} else 
				cons.logtime[cons.log_it] = 0;
			memcpy(cons.log[cons.log_it], nl_ptr, strchr(nl_ptr, '\n') - nl_ptr);
			puts(cons.log[cons.log_it]);
			nl_ptr = strchr(nl_ptr, '\n') + 1;
			cons.log_it++;
		}
	}
}

static inline void skip_spaces(char **s){
	while (**s == ' ')
		(*s)++;
}

static inline bool missing_arg(char *s) {
	if (*s == '\0'){
		console_println("Missing arguments");
		return (true);
	}
	return (false);
}

static void console_parse_object(char *cmd) {
	object tmp_obj;

	(void)tmp_obj;
	// just command without parameters
	if (strchr(cmd, ' ') == NULL){
		console_println("No arguments provided to add_obj");
		return ;
	}
	
	// parsing the object name
	cmd = strchr(cmd, ' ');
	skip_spaces(&cmd);
	if (missing_arg(cmd) == false)
		return;

	// paranoia
	if (strchr(cmd, ' ') == NULL){
		console_println("No arguments provided to add_obj");
		return ;
	}
	
	// tmp_obj = malloc(strchr(cmd - 	) - cmd)

	
	
}

// processing the command to the command line
static void console_process_line(){
	char *line = cons.cline;

	console_println(cons.cline);

	// here is where we treat the command
	if (strcmp(line, "help") == 0){
		console_println(CONS_HELP);
	} else if (strcmp(line, "clear") == 0) {
		console_clear();
	} else if (strcmp(line, "add_obj") == 0) {
		console_parse_object(line);
	} else 
		console_println("Unknown command, ignoring");
	
	memset(cons.cline, 0, MAX_LINE);
	line_it = 0;
}

void console_open(void){
	console_print_logs();
	if (console_input_box() == true)
		console_process_line();

}
