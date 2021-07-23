#include "coords.h"

#ifndef UCIRCLE_H
#define UCIRCLE_H

double ucircle_coords_to_radians(struct coords_t coords);
struct coords_t ucircle_radians_to_coords(double angle);

#endif