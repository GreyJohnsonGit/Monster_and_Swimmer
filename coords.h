#ifndef COORDS_H
#define COORDS_H

struct coords_t;
struct coords_t coords_init(double x, double y);
struct coords_t coords_copy(struct coords_t coords);
struct coords_t coords_scale(double factor, struct coords_t coords);
struct coords_t coords_normalize(struct coords_t coords);
struct coords_t coords_sum(struct coords_t coords_left, struct coords_t coords_right);
double coords_dot_product(struct coords_t coords_left, struct coords_t coords_right);
void coords_print(struct coords_t coords);

struct coords_t
{
    double x;
    double y;
};

#endif