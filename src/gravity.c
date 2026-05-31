#include <space-time.h>

void apply_gravity_all_objs(coord_3d *point){
	object *obj_it = objs;
	uint64_t r;
	while (obj_it != NULL) {
		r = sqrt(
			pow(obj.coords.x - point->x, 2) + 
			pow(obj.coords.y - point->y, 2) + 
			pow(obj.coords.z - point->z, 2) + 
			)
	}

}

void apply_gravity(object *obj, coord_3d *point) {

}
