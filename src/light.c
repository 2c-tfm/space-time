#include <space_time.h>

// static void draw_photon_trail(object *target){
// 	object *trg_trail = MemAlloc(sizeof(object));
// 	uint32_t i = 0;
//
// 	memcpy(trg_trail, target, sizeof(object));
// 	while (i < TRAIL_LEN){
// 		trg_trail->coords.x -= trg_trail->acceleration.x;
// 		trg_trail->coords.y -= trg_trail->acceleration.y;
// 		trg_trail->coords.z -= trg_trail->acceleration.z;
//
// 		coord_2d trail_proj = orthographic_projection(&trg_trail->coords);
//
// 		DrawPixel(trail_proj.x, trail_proj.y, WHITE);
// 		i++;
// 	}
// 	MemFree(trg_trail);
// }

void space_update_photon(object *photon){
	coord_3d after_bend;
	coord_3d bend;
	coord_3d dir;

	memcpy(&after_bend, &photon->coords, sizeof(coord_3d));
	apply_gravity_on_space(&after_bend);

	bend.x = after_bend.x - photon->coords.x;
	bend.y = after_bend.y - photon->coords.y;
	bend.z = after_bend.z - photon->coords.z;

	// Normalize the bend direction
	double bend_len = sqrt(bend.x*bend.x + bend.y*bend.y + bend.z*bend.z);
	if (bend_len > 0.0001) {
		bend.x /= bend_len;
		bend.y /= bend_len;
		bend.z /= bend_len;
	}

	memcpy(&dir, &photon->acceleration, sizeof(coord_3d));

	// bend strength is used to keep 
	dir.x = dir.x * (1.0 - BEND_STRENGTH) + bend.x * BEND_STRENGTH;
	dir.y = dir.y * (1.0 - BEND_STRENGTH) + bend.y * BEND_STRENGTH;
	dir.z = dir.z * (1.0 - BEND_STRENGTH) + bend.z * BEND_STRENGTH;

	double displ_mgn = sqrt(dir.x*dir.x + dir.y*dir.y + dir.z*dir.z);
	if (displ_mgn > 0.0001) {
		dir.x /= displ_mgn;
		dir.y /= displ_mgn;
		dir.z /= displ_mgn;
	}

	memcpy(&photon->acceleration, &dir, sizeof(coord_3d));	// storing it back
	photon->coords.x += photon->acceleration.x * 10;
	photon->coords.y += photon->acceleration.y * 10;
	photon->coords.z += photon->acceleration.z * 10;
}


void space_cast_photon(coord_3d *pcoords, coord_3d *acceleration) {
	object *photon = MemAlloc(sizeof(object));
	photon->name = strdup("photonX");
	photon->radius = 1;
	photon->mass = 0;
	memcpy(&photon->acceleration, acceleration, sizeof(coord_3d));
	memcpy(&photon->coords, pcoords, sizeof(coord_3d));
	memset(&photon->velocity, 0, sizeof(coord_3d));
	printf("");
	photon->colors[0] = WHITE;
	photon->colors[1] = YELLOW;
	photon->type = PHOTON;
	photon->active = true;
	photon->next = NULL;
	add_space_object(photon);
	console_println("Photon Added to space");
	print_all_space_object();
}
