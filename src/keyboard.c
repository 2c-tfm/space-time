#include <space_time.h>

bool dspace = false;

void handle_keys(void){
	if (IsKeyPressed(KEY_F)) {
		dspace = !dspace;
	}
}
