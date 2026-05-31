#include <space_time.h>


object *objs;

object *init_space_objects(){
	object *mars = MemAlloc(sizeof(object));
	mars->name = "mars (planet)";
	mars->mass = 1000;  // make it dominant
	mars->radius = 7;
	mars->coords.x = 10;
	mars->coords.y = 10;
	mars->coords.z = 10;
	mars->velocity.x = 0;
	mars->velocity.y = 0;
	mars->velocity.z = 0;
	mars->acceleration.x = 0;
	mars->acceleration.y = 0;
	mars->acceleration.z = 0;
	mars->colors[0] = RED;
	mars->colors[1] = ORANGE;
	mars->next = MemAlloc(sizeof(object));
	
	object *phobos = mars->next;
	phobos->name = "phobos (moon)";
	phobos->mass = 1;
	phobos->radius = 2;
	phobos->coords.x = 30;
	phobos->coords.y = 0;
	phobos->coords.z = 0;
	phobos->acceleration.x = 0;
	phobos->acceleration.y = 0;
	phobos->acceleration.z = 0;
	phobos->colors[0] = LIGHTGRAY;
	phobos->colors[1] = DARKGRAY;
	phobos->next = NULL;
	// phobos->next = MemAlloc(sizeof(object));

	// object *zebi = phobos->next;
	// zebi->name = "planetdzp (planet)";
	// zebi->mass = 3000;
	// zebi->radius = 5;
	// zebi->coords.x = 0;
	// zebi->coords.y = 0;
	// zebi->coords.z = 0;
	// zebi->velocity.x = 0;
	// zebi->velocity.y = 0;
	// zebi->velocity.z = 0;
	// zebi->acceleration.x = 0;
	// zebi->acceleration.y = 0;
	// zebi->acceleration.z = 0;
	// zebi->colors[0] = BLUE;
	// zebi->colors[1] = SKYBLUE;
	// zebi->next = NULL;

	// Calculate Phobos orbital velocity around Mars
	double dx = mars->coords.x - phobos->coords.x;
	double dy = mars->coords.y - phobos->coords.y;
	double dz = mars->coords.z - phobos->coords.z;
	double r = sqrt(dx*dx + dy*dy + dz*dz);
	double orbital_speed = sqrt(GRAVITY_CONST * mars->mass / r);
	
	// Perpendicular direction (cross product with Y axis since on X axis)
	double perp_x = -dz;  // 0
	double perp_y = 0;
	double perp_z = dx;   // -50
	double perp_len = sqrt(perp_x*perp_x + perp_y*perp_y + perp_z*perp_z);
	
	phobos->velocity.x = (perp_x / perp_len) * orbital_speed;
	phobos->velocity.y = (perp_y / perp_len) * orbital_speed;
	phobos->velocity.z = (perp_z / perp_len) * orbital_speed;

	return mars;
}
