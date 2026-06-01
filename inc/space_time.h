#ifndef SPACE_TIME_H
#define SPACE_TIME_H
/////////////////////////////////// TODO ///////////////////////////////////
/// [X] - simulate space 
/// [X] - create objects 
////// [X] - draw objects on the plane
/// [X] - simulate gravity warp in space
/// [X] - fix that anoying segv
/// [X] - fix the space warp 
/// [x] - apply gravity on masses
/// [x] - apply an orbit
/// [x] - find out how to create unlimited space fabric
/// [x] - allow planets from a json file
/// [x] - init their velocity 
/// [X] - adding a trail for objects 
/// [ ] - shine light wave (using mouse)
////// [ ] - replace camera dragging control controls (SHIFT + mouse drag) instead of (mouse drag)
/// [ ] - electro magnetic field of a planet
/// [ ] - maybe emulate a star???/
/// [ ] - add a menu for instructions
/////////////////////////////////// TODO ///////////////////////////////////

///////////////////////////////// includes /////////////////////////////////
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <raylib.h>
#include <string.h>
#include <cJSON.h>


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
// keyboard controls
void handle_keys(void);
///////////////////////////////// functions ////////////////////////////////

extern bool dspace;
extern double focal_length;
extern Vector2 cameraOffset;
extern double alpha;

#endif
