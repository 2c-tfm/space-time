#include <space_time.h>

void render_frame(void){
	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(BLACK);
		draw_space();
		EndDrawing();
	}
	CloseWindow();
}
