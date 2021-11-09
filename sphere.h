#ifndef RAYTRACE_SPHERE
#define RAYTRACE_SPHERE
#include "matrix.h"

typedef struct Sphere {
    int id;
    Matrix4 transform;
} Sphere;

Sphere sphere_make();
Sphere *sphere_set_transform(Sphere *s, Matrix4 t);
#endif
