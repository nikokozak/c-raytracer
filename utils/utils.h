#ifndef RAYTRACER_UTILS
#define RAYTRACER_UTILS

#include <stdbool.h>
#include <math.h>

bool utils_fequals(double a, double b);
double utils_clamp(double in, double min, double max);
int utils_rf_index(int x, int y, int width);

#endif
