#include "sphere.h"
#include <stdlib.h>

Sphere sphere_make()
{
    return (Sphere) { rand(),
    matrix4_identity() };
}

Sphere *sphere_set_transform(Sphere *s, Matrix4 t)
{
    s->transform = t;
    return s;
}
