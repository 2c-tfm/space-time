#ifndef SPACE_TIME_H
#define SPACE_TIME_H
/////////////////////////////////// TODO ///////////////////////////////////
/// [X] - simulate space 
/// [X] - create objects 
////// [X] - draw objects on the plane
/// [X] - simulate gravity warp in space
/// [X] - fix that anoying segv
/// [X] - fix the space warp 
/// [ ] - apply gravity on masses
/// [ ] - apply an orbit
/// [ ] - find out how to create unlimited space fabric
/////////////////////////////////// TODO ///////////////////////////////////

///////////////////////////////// includes /////////////////////////////////
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <raylib.h>
#include <string.h>


#include "space.h"
#include "object.h"
#include "graphics.h"
#include "gravity.h"
///////////////////////////////// includes /////////////////////////////////


//////////////////////////////// definitions ///////////////////////////////

#define WIN_NAME "SPACE-TIME"
#define WIN_X 800
#define WIN_Y 800

//////////////////////////////// definitions ///////////////////////////////

///////////////////////////////// functions ////////////////////////////////
// mouse controls
void handle_drag(void);
void handle_zoom(void);
///////////////////////////////// functions ////////////////////////////////

extern double focal_length;
extern Vector2 cameraOffset;
extern double alpha;

#endif
