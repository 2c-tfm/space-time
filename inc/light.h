#ifndef LIGHT_H
#define LIGHT_H

void space_cast_photon(coord_3d *pcoords, coord_3d *acceleration);
void space_update_photon(object *photon);

#define BEND_STRENGTH 0.01

#endif
