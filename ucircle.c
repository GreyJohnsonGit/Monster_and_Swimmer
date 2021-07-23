#include <math.h>
#include "ucircle.h"

// I'm sure I can come up with a cleaner and branchless algorithm, but this is fine.
double ucircle_coords_to_radians(struct coords_t coords)
{
    double angle;
    if (coords.x != 0)
        angle = atan(coords.y / coords.x);
    else
        angle = M_PI_2;

    if (coords.x >= 0 && coords.y >= 0)
        return angle;
    if (coords.x < 0 && coords.y >= 0)
        return angle + M_PI;
    if (coords.x <= 0 && coords.y < 0)
        return angle + M_PI;
    if (coords.x > 0 && coords.y < 0)
        return angle + 2 * M_PI;
}

struct coords_t ucircle_radians_to_coords(double angle)
{
    struct coords_t new_coords = {
        cos(angle),
        sin(angle),
    };
    return new_coords;
}