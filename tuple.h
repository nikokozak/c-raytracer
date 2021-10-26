#include <stdbool.h>

typedef struct Tuple {
    double x;
    double y;
    double z;
    double w;
} Tuple;

Tuple tuple_make_tuple(double, double, double, double);
Tuple tuple_make_point(double, double, double);
Tuple tuple_make_vector(double, double, double);

bool tuple_is_point(Tuple);
bool tuple_is_vector(Tuple);
double tuple_magnitude(Tuple);
double tuple_dot(Tuple, Tuple);

Tuple tuple_add(Tuple, Tuple);
Tuple tuple_sub(Tuple, Tuple);
Tuple tuple_negate(Tuple);
Tuple tuple_mult(Tuple, double);
Tuple tuple_div(Tuple, double);
Tuple tuple_normalize(Tuple);
Tuple tuple_cross(Tuple, Tuple);
