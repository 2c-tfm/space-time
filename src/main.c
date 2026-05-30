#include <space_time.h>

int main(void){
	InitWindow(WIN_X, WIN_Y, WIN_NAME);
	SetTargetFPS(60);

	theta = atan(1/sqrt(2));
	objs = init_space_objects();

	render_frame();
	return (0);
}
