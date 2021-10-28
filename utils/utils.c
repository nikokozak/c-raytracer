#include "utils.h"

const double EPSILON = 0.00001;

bool utils_fequals(double a, double b)
{
    return (fabs(a - b) < EPSILON) ? true : false;
}

double utils_clamp(double in, double min, double max)
{
    const double t = in < min ? min : in;
    return (int) t > max ? max : t;
}

int utils_rf_index(int x, int y, int width)
{
    return x + (y * width);
}
