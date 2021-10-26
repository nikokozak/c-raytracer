#include "tuple.h"
#include "utils.h"

Tuple tuple_make_tuple(double x, double y, double z, double w)
{
    return (Tuple) { x, y, z, w };
}

Tuple tuple_make_point(double x, double y, double z)
{
    return tuple_make_tuple(x, y, z, 1.0);
}

Tuple tuple_make_vector(double x, double y, double z)
{
    return tuple_make_tuple(x, y, z, 0.0);
}

bool tuple_is_point(Tuple *tuple)
{
    return (utils_fequals(tuple->w, 1.0)) ? true : false;
}

bool tuple_is_vector(Tuple *tuple)
{
    return (utils_fequals(tuple->w, 0.0)) ? true : false;
}

Tuple tuple_add(Tuple *a, Tuple *b)
{
    return (Tuple) { a->x + b->x,
        a->y + b->y,
        a->z + b->z,
        a->w + b->w };
}
