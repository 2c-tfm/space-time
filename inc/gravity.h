#ifndef GRAVITY_H
#define GRAVITY_H

#define GRAVITY_CONST 1.5
#define PHYSICS_DT (1.0 / 240.0)

void apply_gravity_on_space(coord_3d *point);
void calc_all_objs_gforce(void);
void obj_update_coords_via_accel(void);


#endif
