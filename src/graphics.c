#include <space_time.h>

void info(){
	DrawText("1 unit = 10,000 KM", 30, WIN_Y - 100, 10,  LIGHTGRAY);
}

void render_frame(void){
	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(BLACK);
		handle_zoom();
		handle_drag();
		info();
		draw_space();
		draw_objects();
		EndDrawing();
	}
	CloseWindow();
}
