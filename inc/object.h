#ifndef OBJECT_H
#define OBJECT_H

typedef struct object {
	uint64_t mass;
	uint64_t radius;			// in px
	struct coord_3d coords;
	struct object *next;			// might change this later
} object;

extern object *objs;

object *init_space_objects();

#endif
