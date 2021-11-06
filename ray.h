#ifndef RAYTRACE_RAYS
#define RAYTRACE_RAYS
#include "tuple.h"
#include "sphere.h"

typedef struct Ray {
    Tuple origin;
    Tuple direction;
} Ray;

typedef struct Intersect { 
    int count;
    double t[2];
} Intersect;

Ray ray_make(Tuple point_origin, Tuple vector_direction);
Tuple ray_position(Ray ray, double t);
Intersect ray_intersect(Sphere s, Ray r);
#endif
