#include <space_time.h>

void handle_zoom(void) {
	printf("focal length %lf\n", focal_length);
	if (focal_length < 20 && GetMouseWheelMove() < 0.0f)
		return;
	focal_length += GetMouseWheelMove() * 10;
	if (focal_length < 0.1f) 
		focal_length = 0.1f;
}

void handle_drag(void){
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
