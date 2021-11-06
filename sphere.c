#include "sphere.h"
#include <stdlib.h>

Sphere sphere_make()
{
    return (Sphere) { rand() };
}
