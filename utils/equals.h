#ifndef EPSILON_EQUALS
#define EPSILON_EQUALS

#include <stdbool.h>
#include <math.h>

const double EPSILON = 0.00001;

bool equals_double(double a, double b)
{
    return (fabs(a - b) < EPSILON) ? true : false;
}

#endif
