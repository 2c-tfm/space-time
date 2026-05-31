#ifndef SPACE_H
#define SPACE_H

extern double theta;

///////////////////////////////// structs /////////////////////////////////

typedef struct coord_3d {
	double x;
	double y;
	double z;
} coord_3d;

typedef struct coord_2d {
	double x;
	double y;
} coord_2d;

///////////////////////////////// structs /////////////////////////////////


void draw_objects(void);
void draw_space(void);

#endif
