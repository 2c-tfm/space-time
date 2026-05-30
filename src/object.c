#include <space_time.h>


object *objs;

// init_space_objects - for now we init space objects manually
object *init_space_objects(){
	object *mainobj = MemAlloc(sizeof(objs));
	mainobj->mass = 6969;
	mainobj->radius = 1;
	mainobj->coords.x = 4;
	mainobj->coords.y = 4;
	mainobj->coords.z = 4;
	mainobj->next = NULL;
	return mainobj;
}
