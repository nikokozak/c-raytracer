#include "utils.h"

const double EPSILON = 0.00001;

bool utils_fequals(double a, double b)
{
    return (fabs(a - b) < EPSILON) ? true : false;
}
