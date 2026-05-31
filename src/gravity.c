#include <space_time.h>

/// shift_amount = G * M / r²
void apply_gravity_all_objs(coord_3d *point){
	object *obj = objs;
	double total_dx = 0;
	double total_dy = 0;
	double total_dz = 0;

	while (obj != NULL) {
		double dx = obj->coords.x - point->x;
		double dy = obj->coords.y - point->y;
		double dz = obj->coords.z - point->z;
		double r = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
		if (r < 0.001){
			obj = obj->next;
			continue;
		}
		double shift = (GRAVITY_CONST * obj->mass / pow(r, 2));
		total_dx += (dx/r)*shift;
		total_dy += (dy/r)*shift;
		total_dz += (dz/r)*shift;
		obj = obj->next;
	}
	point->x += total_dx;
	point->y += total_dy;
	point->z += total_dz;
}


void apply_gravity(object *obj, coord_3d *point) {
	(void) obj;
	(void) point;
}
