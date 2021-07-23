#include <stdio.h>
#include <math.h>
#include "coords.h"

struct coords_t coords_init(double x, double y)
{
    struct coords_t new_coords = {x, y};
    return new_coords;
}

struct coords_t coords_copy(struct coords_t coords)
{
    struct coords_t new_coords = {coords.x, coords.y};
    return new_coords;
}

struct coords_t coords_scale(double factor, struct coords_t coords)
{
    struct coords_t new_coords = {coords.x * factor, coords.y * factor};
    return new_coords;
}

struct coords_t coords_normalize(struct coords_t coords)
{
    double magnitude_squared = coords_dot_product(coords, coords);
    if (magnitude_squared == 0)
        return coords;
    double magnitude = sqrt(magnitude_squared);
    return coords_scale(1 / magnitude, coords);
}

double coords_dot_product(struct coords_t coords_left, struct coords_t coords_right)
{
    return coords_left.x * coords_right.x + coords_left.y * coords_right.y;
}

struct coords_t coords_sum(struct coords_t coords_left, struct coords_t coords_right)
{
    struct coords_t new_coords = {coords_left.x + coords_right.x, coords_left.y + coords_right.y};
    return new_coords;
}

void coords_print(struct coords_t coords)
{
    printf("(x:%lf, y:%lf)", coords.x, coords.y);
}