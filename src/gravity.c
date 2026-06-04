#include <space_time.h>

void calc_orbiter_velocity(object *obj, object *centralbody){
	double dx = centralbody->coords.x - obj->coords.x;
	double dy = centralbody->coords.y - obj->coords.y;
	double dz = centralbody->coords.z - obj->coords.z;
	double r = sqrt(dx*dx + dy*dy + dz*dz);

	double orbital_speed = sqrt(GRAVITY_CONST * centralbody->mass / r);

	double perp_x = -dz;  // 0
	double perp_y = 0;
	double perp_z = dx;   // -50
	double perp_len = sqrt(perp_x*perp_x + perp_y*perp_y + perp_z*perp_z);

	obj->velocity.x = (perp_x / perp_len) * orbital_speed;
	obj->velocity.y = (perp_y / perp_len) * orbital_speed;
	obj->velocity.z = (perp_z / perp_len) * orbital_speed;
}

/// shift_amount = G * M / r²
void apply_gravity_on_space(coord_3d *point){
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

void obj_update_coords_via_accel(){
	object *obj_it = objs;

	while (obj_it != NULL){
		obj_it->velocity.x += obj_it->acceleration.x * PHYSICS_DT;
		obj_it->velocity.y += obj_it->acceleration.y * PHYSICS_DT;
		obj_it->velocity.z += obj_it->acceleration.z * PHYSICS_DT;

		obj_it->coords.x += obj_it->velocity.x * PHYSICS_DT;
		obj_it->coords.y += obj_it->velocity.y * PHYSICS_DT;
		obj_it->coords.z += obj_it->velocity.z * PHYSICS_DT;

		obj_it = obj_it->next;
	}
}

// calculates the force of gravity between two objects;
void calc_objs_gforce(object *target){
	object *obj_it = objs;

	// Reset acceleration
	target->acceleration.x = 0;
	target->acceleration.y = 0;
	target->acceleration.z = 0;

	while (obj_it != NULL){
		if (target == obj_it) {
			obj_it = obj_it->next;
			continue;
		}
		double dx = obj_it->coords.x - target->coords.x;
		double dy = obj_it->coords.y - target->coords.y;
		double dz = obj_it->coords.z - target->coords.z;

		double r = sqrt(dx*dx + dy*dy + dz*dz);

		if (r < 0.001){
			obj_it = obj_it->next;
			continue;
		}

		double accel_mg = GRAVITY_CONST * obj_it->mass / (r*r);

		target->acceleration.x += (dx / r) * accel_mg;
		target->acceleration.y += (dy / r) * accel_mg;
		target->acceleration.z += (dz / r) * accel_mg;
		obj_it = obj_it->next;
	}
}

void calc_all_objs_gforce(void){
	object *obj_it = objs;

	while (obj_it != NULL){
		if (obj_it->type == PRIMARY || obj_it->type == SECONDARY)
			calc_objs_gforce(obj_it);
		obj_it = obj_it->next;
	}
}

