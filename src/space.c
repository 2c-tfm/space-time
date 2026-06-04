#include <space_time.h>

bool trail = true;

bool pause_siml = false;
double focal_length = 60;
Vector2 cameraOffset = {0, 0};
double theta ;
double alpha =  M_PI / 4.0;

// orthographic_projection - projects a 3d point onto a 2d plane
coord_2d orthographic_projection(coord_3d *coord) {

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

static void draw_obj_trail(object *target){
	object *trg_trail = MemAlloc(sizeof(object));
	struct Color trail_temp = RED;
	uint32_t i = 0;

	memcpy(trg_trail, target, sizeof(object));
	while (i < TRAIL_LEN){
		trg_trail->velocity.x -= trg_trail->acceleration.x * PHYSICS_DT;
		trg_trail->velocity.y -= trg_trail->acceleration.y * PHYSICS_DT;
		trg_trail->velocity.z -= trg_trail->acceleration.z * PHYSICS_DT;

		trg_trail->coords.x -= trg_trail->velocity.x * PHYSICS_DT;
		trg_trail->coords.y -= trg_trail->velocity.y * PHYSICS_DT;
		trg_trail->coords.z -= trg_trail->velocity.z * PHYSICS_DT;

		coord_2d trail_proj = orthographic_projection(&trg_trail->coords);
		
		DrawPixel(trail_proj.x, trail_proj.y, trail_temp);

		if (trail_temp.r > 0 && i % 3 == 0)
			trail_temp.r -= 1;
		i++;
	}
	MemFree(trg_trail);
}

void draw_objects(void){
	object *obj_it = objs;

	calc_all_objs_gforce();

	if (pause_siml == false){
		obj_update_coords_via_accel();
	}

	// iterating over objects to draw
	while (obj_it != NULL) {
		coord_2d proj = orthographic_projection(&obj_it->coords);
		Vector2 cords = {proj.x, proj.y};
		DrawText(obj_it->name, proj.x - obj_it->radius * 
				(focal_length * 1.2),proj.y - obj_it->radius
				* focal_length -3,(-2 * focal_length), LIGHTGRAY);
		DrawCircleGradient(cords, obj_it->radius * (focal_length * 0.2),
				obj_it->colors[0], obj_it->colors[1]);
		if ((obj_it->type == PRIMARY || obj_it->type == SECONDARY) && trail)
			draw_obj_trail(obj_it);
		if (obj_it->type == PHOTON && pause_siml == false) {
			space_update_photon(obj_it);
		}
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
	
	(void) screen_range;
	while (init.x < 80) {
		init.y = 0.00001f;
		while (init.y < 80) {
			init.z = 0.00001f;
			while (init.z < 80){
				memcpy(pgrav, &init, sizeof(coord_3d));

				apply_gravity_on_space(pgrav);

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
