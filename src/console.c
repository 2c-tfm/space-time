#include <space_time.h>

console cons = {
	.open = false,
	.clog_it = 0,
};

void console_open(void){
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight() / 2, Fade(BLACK, 0.5f));

}
