#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <math.h>
#include <stdio.h>
#include "ray.h"
#include "sphere.h"
#include "utils.h"

static void creates_a_ray(void **state)
{
    Tuple origin = tuple_make_point(1.0, 2.0, 3.0);
    Tuple direction = tuple_make_vector(4.0, 5.0, 6.0);
    Ray a = ray_make(origin, direction);

    assert_true(tuple_equal(a.origin, origin));
    assert_true(tuple_equal(a.direction, direction));
}

static void computes_a_point_from_distance(void **state)
{
    Tuple origin = tuple_make_point(2.0, 3.0, 4.0);
    Tuple direction = tuple_make_vector(1.0, 0.0, 0.0);
    Ray a = ray_make(origin, direction);

    assert_true(tuple_equal(ray_position(a, 0.0), tuple_make_point(2.0, 3.0, 4.0)));
    assert_true(tuple_equal(ray_position(a, 1.0), tuple_make_point(3.0, 3.0, 4.0)));
    assert_true(tuple_equal(ray_position(a, -1.0), tuple_make_point(1.0, 3.0, 4.0)));
    assert_true(tuple_equal(ray_position(a, 2.5), tuple_make_point(4.5, 3.0, 4.0)));
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(creates_a_ray),
        cmocka_unit_test(computes_a_point_from_distance),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
