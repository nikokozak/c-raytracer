#ifndef RAYTRACE_RAYS
#define RAYTRACE_RAYS
#include "tuple.h"
#include "matrix.h"
#include "sphere.h"

typedef struct Ray {
    Tuple origin;
    Tuple direction;
} Ray;

typedef struct Intersection {
    Sphere *object;
    double t;
} Intersection;

typedef struct Intersect { 
    int count;
    Intersection i[2];
} Intersect;

Ray ray_make(Tuple point_origin, Tuple vector_direction);
Tuple ray_position(Ray ray, double t);
Intersect ray_intersect(Sphere *s, Ray r);
Intersection ray_intersection(double t, Sphere *s);
bool ray_intersection_equal(Intersection i1, Intersection i2);
Intersection *ray_hit(int count, Intersection *ints[]);
Ray ray_transform(Ray r, Matrix4 m);
#endif
