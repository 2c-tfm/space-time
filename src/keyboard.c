#include <space_time.h>

bool dspace = false;

void handle_keys(void){
	if (IsKeyPressed(KEY_ESCAPE)) {
		cons.open = !cons.open;
	}
	if (cons.open == true)
		return;

	if (IsKeyPressed(KEY_F)) {
		dspace = !dspace;
	}

	if (IsKeyPressed(KEY_T)) {
		trail = !trail;
	}

	if (IsKeyPressed(KEY_Q)) {
		exit(EXIT_SUCCESS);
	}

	// handling camera offset 
	if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){
		cameraOffset.y +=  20;
	} else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)){
		cameraOffset.y -=  20;
	} else if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)){
		cameraOffset.x -=  20;
	} else if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)){
		cameraOffset.x +=  20;
	}

}
