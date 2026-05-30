#include <space_time.h>

double focal_length = 5;
Vector2 cameraOffset = {0, 0};
double theta ;
double alpha = 45;



// orthographic_projection - projects a 3d point onto a 2d plane
static coord_2d orthographic_projection(coord_3d *coord) {

	double px = coord->x * cos(alpha) + coord->z * sin(alpha);
	double pz = -coord->x * cos(alpha) + coord->z * sin(alpha);
	double py = coord->y;
	double tempY = py * cos(theta) - pz * sin(theta);
	double tempZ = py * sin(theta) + pz * cos(theta);

	py = tempY;
	pz = tempZ;

	coord_2d proj = {
		.x = (px * focal_length) + (WIN_X / 2) + cameraOffset.x,
		.y = (py * focal_length) + (WIN_Y / 2) + cameraOffset.y,
	};

	return (proj);
}

static void handle_zoom(void) {
	focal_length += GetMouseWheelMove() * 10;
	if (focal_length < 0.1f) 
		focal_length = 0.1f;
}

static void handle_drag(void){
	static bool dragging = false;
	static Vector2 prevMousePos = {0, 0};
	static Vector2 dragDelta = {0, 0};

	Vector2 mousePos = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		dragging = true;
		prevMousePos = mousePos;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		dragging = false;
		dragDelta = (Vector2){0, 0};
        }

        if (dragging && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		cameraOffset.y += (mousePos.y - prevMousePos.y) * 0.5;
		cameraOffset.x += (mousePos.x - prevMousePos.x) * 0.5;
		prevMousePos = mousePos;
        }


        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
		dragging = true;
		prevMousePos = mousePos;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
		dragging = false;
		dragDelta = (Vector2){0, 0};
        }

        if (dragging && IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		theta += (mousePos.y - prevMousePos.y) * 0.01;
		alpha += (mousePos.x - prevMousePos.x) * 0.01;
		prevMousePos = mousePos;
        }
}

void draw_space(){
	handle_zoom();
	handle_drag();

	coord_3d init = {
		.x = 0.1f, 
		.y = 0.1f,
		.z = 0.1f
	};
	object *obj_it = objs;
	printf("basic object %p %p\n",(void *) obj_it, (void *)obj_it->next);

	// iterating over objects to draw
	while (obj_it != NULL) {
		coord_2d proj = orthographic_projection(&obj_it->coords);
		Vector2 cords = {proj.x, proj.y};
		DrawCircleGradient(cords, obj_it->radius * focal_length, ORANGE, SKYBLUE);
		obj_it = obj_it->next;
	}

	while (init.x < 10) {
		init.y = 0.1f;
		while (init.y < 10) {
			init.z = 0.1f;
			while (init.z < 10){
				coord_2d proj = orthographic_projection(&init);
				DrawCircle(proj.x, proj.y, 1.0, LIGHTGRAY);
				init.z += 1;
			}
			init.y += 1;
		}
		init.x++;
	}

}
