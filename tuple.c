#include "tuple.h"
#include "equals.h"

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
    return (equals_double(tuple->w, 1.0)) ? true : false;
}

bool tuple_is_vector(Tuple *tuple)
{
    return (equals_double(tuple->w, 0.0)) ? true : false;
}
