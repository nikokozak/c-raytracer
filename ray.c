#include "ray.h"
#include <math.h>

Ray ray_make(Tuple point_origin, Tuple vector_direction)
{
    return (Ray) { point_origin, vector_direction };
}

Tuple ray_position(Ray ray, double t)
{
    return tuple_add(tuple_mult(ray.direction, t), ray.origin);
}

Intersect ray_intersect(Sphere s, Ray r)
{
    Tuple sphere_to_ray = tuple_sub(r.origin, tuple_make_point(0.0, 0.0, 0.0));

    double a = tuple_dot(r.direction, r.direction);
    double b = tuple_dot(r.direction, sphere_to_ray) * 2.0;
    double c = tuple_dot(sphere_to_ray, sphere_to_ray) - 1.0;

    double discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0) {
        return (Intersect) { 0, 0 };
    }

    double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
    
    return (Intersect) { 2, { t1, t2 } };
}
