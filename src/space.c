#include <space_time.h>

double focal_length = 60;
Vector2 cameraOffset = {0, 0};
double theta ;
double alpha =  M_PI / 4.0;

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

void draw_objects(void){
	object *obj_it = objs;



	// iterating over objects to draw
	while (obj_it != NULL) {
		coord_2d proj = orthographic_projection(&obj_it->coords);
		Vector2 cords = {proj.x, proj.y};
		DrawText(obj_it->name, proj.x - obj_it->radius * (focal_length * 1.2),
				proj.y - obj_it->radius * focal_length -3, (-2 * focal_length),
				LIGHTGRAY);
		DrawCircleGradient(cords, obj_it->radius * (focal_length * 0.2), obj_it->colors[0], obj_it->colors[1]);
		obj_it = obj_it->next;
	}

}


void draw_space(void){
	coord_3d init;
	coord_2d proj;
	coord_3d *pgrav = MemAlloc(sizeof(coord_3d));
	uint32_t screen_range = fmax(WIN_X, WIN_Y) / focal_length;

	memset(&init, 0, sizeof(coord_3d));		// initializing vals
	memset(&proj, 0, sizeof(coord_2d));		// initializing vals
	init.x = 0.00001f;
	

	while (init.x < screen_range) {
		init.y = 0.00001f;
		while (init.y < screen_range) {
			init.z = 0.00001f;
			while (init.z < screen_range){
				memcpy(pgrav, &init, sizeof(coord_3d));

				apply_gravity_all_objs(pgrav);

				proj = orthographic_projection(pgrav);
				DrawPixel(proj.x, proj.y, LIGHTGRAY);
				init.z++;
			}
			init.y++;
		}
		init.x++;
	}
	MemFree(pgrav);
	
}
