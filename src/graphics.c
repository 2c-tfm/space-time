#include <space_time.h>

void info(){
	DrawText("1 unit = 10,000 KM", 30, WIN_Y - 100, 10,  LIGHTGRAY);
}

void render_frame(void){
	calc_all_objs_gforce();
	while(!WindowShouldClose()){
		BeginDrawing();
		handle_zoom();
		handle_drag();
		handle_keys();
		info();
		if (cons.open == false) {
			ClearBackground(BLACK);
			if (dspace)
				draw_space();
			draw_objects();
		} else {
			console_open();
		}
		EndDrawing();
	}
	CloseWindow();
}
