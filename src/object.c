#include <space_time.h>


object *objs;

// init_space_objects - for now we init space objects manually
object *init_space_objects(){
	object *mars = MemAlloc(sizeof(object));
	mars->name = "mars (planet)";
	// mars->mass = pow(10,23) * 3.301;
	mars->mass = 1;
	mars->radius = 7;
	mars->coords.x = 4;
	mars->coords.y = 4;
	mars->acceleration.x = 0;
	mars->acceleration.y = 0;
	mars->acceleration.z = 0;
	mars->coords.z = 4;
	mars->colors[0] = RED;
	mars->colors[1] = ORANGE;
	mars->next = MemAlloc(sizeof(object));
	object *phobos = mars->next;
	phobos->name = "phobos (moon)";
	phobos->mass = 1;
	phobos->radius = 2;
	phobos->coords.x = 8;
	phobos->coords.y = 8;
	phobos->coords.z = 8;
	phobos->velocity.x = 0;
	phobos->velocity.y = 0;
	phobos->velocity.z = 14.14;
	phobos->acceleration.x = 0;
	phobos->acceleration.y = 0;
	phobos->acceleration.z = 0;
	phobos->colors[0] = LIGHTGRAY;
	phobos->colors[1] = DARKGRAY;
	phobos->next = NULL;


	return mars;
}
