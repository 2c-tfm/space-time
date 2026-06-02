#ifndef OBJECT_H
#define OBJECT_H


typedef struct object {
	char *name;
	double mass;
	uint64_t radius;			// in px
	struct coord_3d acceleration;
	struct coord_3d velocity;
	struct coord_3d coords;
	struct Color colors[2];
	struct object *next;			// might change this later
} object;

extern object *objs;

Color color_from_name(char *name);
void init_space_objects(char *cfg);
void print_all_space_object();

#endif
