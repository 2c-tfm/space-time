#include <space_time.h>

// static void apply_gravity_on_photon(coord_3d *point){
// 	object *obj = objs;
// 	double total_dx = 0;
// 	double total_dy = 0;
// 	double total_dz = 0;
//
// 	while (obj != NULL) {
// 		double dx = obj->coords.x - point->x;
// 		double dy = obj->coords.y - point->y;
// 		double dz = obj->coords.z - point->z;
// 		double r = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
// 		if (r < 0.001){
// 			obj = obj->next;
// 			continue;
// 		}
// 		double shift = (GRAVITY_CONST * 2 * obj->mass / pow(r, 2));
// 		total_dx += (dx/r)*shift;
// 		total_dy += (dy/r)*shift;
// 		total_dz += (dz/r)*shift;
// 		obj = obj->next;
// 	}
// 	point->x += total_dx;
// 	point->y += total_dy;
// 	point->z += total_dz;
// }

void space_update_photon(object *photon){
	coord_3d point;		// before bending
	coord_3d g_vec;		// gravity bending vector
	
	memcpy(&point, &photon->coords, sizeof(coord_3d));
	apply_gravity_on_space(&point);				// TODO : needs to be changed to photon
	
	g_vec.x = point.x - photon->coords.x;
	g_vec.y = point.y - photon->coords.y;
	g_vec.z = point.z - photon->coords.z;

	// applying general relativity (newtonian bend multiplication by 2)
	photon->velocity.x += g_vec.x * 2.0f ;
	photon->velocity.y += g_vec.y * 2.0f ;
	photon->velocity.z += g_vec.z * 2.0f ;

	// normalizing that fucking velocity vector
	double v_mag = sqrt(photon->velocity.x * photon->velocity.x + 
                        photon->velocity.y * photon->velocity.y + 
                        photon->velocity.z * photon->velocity.z);

	if (v_mag > 0.0001f){
		photon->velocity.x = (photon->velocity.x / v_mag) * SIM_SPEED_OF_LIGHT;
		photon->velocity.y = (photon->velocity.y / v_mag) * SIM_SPEED_OF_LIGHT;
		photon->velocity.z = (photon->velocity.z / v_mag) * SIM_SPEED_OF_LIGHT;
	}
	photon->coords.x += photon->velocity.x;
	photon->coords.y += photon->velocity.y;
	photon->coords.z += photon->velocity.z;
}

void space_cast_photon(coord_3d *pcoords, coord_3d *direction) {
	object *photon = MemAlloc(sizeof(object));
	photon->name = strdup("photonX");
	photon->radius = 1;
	photon->mass = 0;
	photon->velocity.x = direction->x * SIM_SPEED_OF_LIGHT;
	photon->velocity.y = direction->y * SIM_SPEED_OF_LIGHT;
	photon->velocity.z = direction->z * SIM_SPEED_OF_LIGHT;
	memset(&photon->acceleration, 0, sizeof(coord_3d));
	memcpy(&photon->coords, pcoords, sizeof(coord_3d));
	photon->colors[0] = WHITE;
	photon->colors[1] = YELLOW;
	photon->type = PHOTON;
	photon->active = true;
	photon->next = NULL;
	add_space_object(photon);
	console_println("Photon Added to space");
}
