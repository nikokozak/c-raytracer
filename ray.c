#include "ray.h"
#include "utils.h"
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

Ray ray_make(Tuple point_origin, Tuple vector_direction)
{
    return (Ray) { point_origin, vector_direction };
}

Tuple ray_position(Ray ray, double t)
{
    return tuple_add(tuple_mult(ray.direction, t), ray.origin);
}

Intersection ray_intersection(double t, Sphere *s)
{
    return (Intersection) { s, t };
}

bool ray_intersection_equal(Intersection i1, Intersection i2)
{
    return utils_fequals(i1.t, i2.t) && i1.object == i2.object;

}

Intersect ray_intersect(Sphere *s, Ray r)
{
    // Adjust Ray location based on sphere transforms.
    Ray r2 = ray_transform(r, matrix4_inverse(s->transform));
    Tuple sphere_to_ray = tuple_sub(r2.origin, tuple_make_point(0.0, 0.0, 0.0));

    double a = tuple_dot(r2.direction, r2.direction);
    double b = tuple_dot(r2.direction, sphere_to_ray) * 2.0;
    double c = tuple_dot(sphere_to_ray, sphere_to_ray) - 1.0;

    double discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0) {
        return (Intersect) { 0, 0 };
    }

    double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
    
    return (Intersect) { 2, 
        { ray_intersection(t1, s), ray_intersection(t2, s) } 
    };
}

Intersection *ray_hit(int count, Intersection *ints[])
{
    Intersection *result = NULL;
    Intersection *current;
    int i;

    for (i = 0; i < count; i++) {
        current = ints[i];
        if ((current->t > 0.0 && ((result != NULL && current->t < result->t) || result == NULL))) {
            result = current;
        } else {
            continue;
        }
    }

    return result;
}

Ray ray_transform(Ray r, Matrix4 m)
{
    // If it's a scaling matrix, affect direction as well.
    if (utils_fequals(m.m[0][3], 0.0) && utils_fequals(m.m[1][3], 0.0) && utils_fequals(m.m[2][3], 0.0)) {
        return (Ray) { matrix4_mult_tuple(m, r.origin), 
            matrix4_mult_tuple(m, r.direction) };
    } else {
        return (Ray) { matrix4_mult_tuple(m, r.origin), r.direction };
    }
}
