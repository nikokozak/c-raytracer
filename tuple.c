#include "tuple.h"
#include "utils.h"

#define TUPLE_POINT_WEIGHT 1.0
#define TUPLE_VECTOR_WEIGHT 0.0

Tuple tuple_make_tuple(double x, double y, double z, double w)
{
    return (Tuple) { x, y, z, w };
}

Tuple tuple_make_point(double x, double y, double z)
{
    return tuple_make_tuple(x, y, z, TUPLE_POINT_WEIGHT);
}

Tuple tuple_make_vector(double x, double y, double z)
{
    return tuple_make_tuple(x, y, z, TUPLE_VECTOR_WEIGHT);
}

bool tuple_is_point(Tuple tuple)
{
    return (utils_fequals(tuple.w, TUPLE_POINT_WEIGHT)) ? true : false;
}

bool tuple_is_vector(Tuple tuple)
{
    return (utils_fequals(tuple.w, TUPLE_VECTOR_WEIGHT)) ? true : false;
}

Tuple tuple_add(Tuple a, Tuple b)
{
    return (Tuple) { a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.w + b.w };
}

Tuple tuple_sub(Tuple a, Tuple b)
{
    return (Tuple) { a.x - b.x,
        a.y - b.y,
        a.z - b.z,
        a.w - b.w };
}

Tuple tuple_mult(Tuple a, double s)
{
    return (Tuple) { a.x * s,
        a.y * s,
        a.z * s,
        a.w * s };
}

Tuple tuple_negate(Tuple a)
{
    return tuple_mult(a, -1.0);
}

Tuple tuple_div(Tuple a, double s)
{
    return (Tuple) { a.x / s,
        a.y / s,
        a.z / s,
        a.w / s };
}

double tuple_magnitude(Tuple a)
{
    return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2) + pow(a.w, 2));
}

Tuple tuple_normalize(Tuple a)
{
    return (Tuple) { a.x / tuple_magnitude(a),
        a.y / tuple_magnitude(a),
        a.z / tuple_magnitude(a),
        a.w / tuple_magnitude(a) };
}

double tuple_dot(Tuple a, Tuple b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Tuple tuple_cross(Tuple a, Tuple b)
{
    return tuple_make_vector(a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x);
}
