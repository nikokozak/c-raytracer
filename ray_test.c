#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <math.h>
#include <stdio.h>
#include "ray.h"
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

static void intersects_a_sphere_at_two_points(void **state)
{
    Tuple origin = tuple_make_point(0.0, 0.0, -5.0);
    Tuple direction = tuple_make_vector(0.0, 0.0, 1.0);
    Ray r = ray_make(origin, direction);
    Sphere s = sphere_make();

    Intersect xs = ray_intersect(s, r);

    assert_int_equal(xs.count, 2);
    assert_true(utils_fequals(xs.t[0], 4.0));
    assert_true(utils_fequals(xs.t[1], 6.0));
}

static void intersects_a_sphere_at_a_tangent(void **state)
{
    Tuple origin = tuple_make_point(0.0, 1.0, -5.0);
    Tuple direction = tuple_make_vector(0.0, 0.0, 1.0);
    Ray r = ray_make(origin, direction);
    Sphere s = sphere_make();

    Intersect xs = ray_intersect(s, r);

    assert_int_equal(xs.count, 2);
    assert_true(utils_fequals(xs.t[0], 5.0));
    assert_true(utils_fequals(xs.t[1], 5.0));
}

static void misses_a_sphere(void **state)
{
    Tuple origin = tuple_make_point(0.0, 2.0, -5.0);
    Tuple direction = tuple_make_vector(0.0, 0.0, 1.0);
    Ray r = ray_make(origin, direction);
    Sphere s = sphere_make();

    Intersect xs = ray_intersect(s, r);

    assert_int_equal(xs.count, 0);
}

static void originates_in_a_sphere(void **state)
{
    Tuple origin = tuple_make_point(0.0, 0.0, 0.0);
    Tuple direction = tuple_make_vector(0.0, 0.0, 1.0);
    Ray r = ray_make(origin, direction);
    Sphere s = sphere_make();

    Intersect xs = ray_intersect(s, r);

    assert_int_equal(xs.count, 2);
    assert_true(utils_fequals(xs.t[0], -1.0));
    assert_true(utils_fequals(xs.t[1], 1.0));
}

static void sphere_is_behind_a_ray(void **state)
{
    Tuple origin = tuple_make_point(0.0, 0.0, 5.0);
    Tuple direction = tuple_make_vector(0.0, 0.0, 1.0);
    Ray r = ray_make(origin, direction);
    Sphere s = sphere_make();

    Intersect xs = ray_intersect(s, r);

    assert_int_equal(xs.count, 2);
    assert_true(utils_fequals(xs.t[0], -6.0));
    assert_true(utils_fequals(xs.t[1], -4.0));
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(creates_a_ray),
        cmocka_unit_test(computes_a_point_from_distance),
        cmocka_unit_test(intersects_a_sphere_at_two_points),
        cmocka_unit_test(intersects_a_sphere_at_a_tangent),
        cmocka_unit_test(misses_a_sphere),
        cmocka_unit_test(originates_in_a_sphere),
        cmocka_unit_test(sphere_is_behind_a_ray),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
