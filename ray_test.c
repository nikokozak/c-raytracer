#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "ray.h"
#include "utils.h"
#include "transform.h"

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

    Intersect xs = ray_intersect(&s, r);

    assert_int_equal(xs.count, 2);
    assert_true(utils_fequals(xs.i[0].t, 4.0));
    assert_true(utils_fequals(xs.i[1].t, 6.0));
}

static void intersects_a_sphere_at_a_tangent(void **state)
{
    Tuple origin = tuple_make_point(0.0, 1.0, -5.0);
    Tuple direction = tuple_make_vector(0.0, 0.0, 1.0);
    Ray r = ray_make(origin, direction);
    Sphere s = sphere_make();

    Intersect xs = ray_intersect(&s, r);

    assert_int_equal(xs.count, 2);
    assert_true(utils_fequals(xs.i[0].t, 5.0));
    assert_true(utils_fequals(xs.i[1].t, 5.0));
}

static void misses_a_sphere(void **state)
{
    Tuple origin = tuple_make_point(0.0, 2.0, -5.0);
    Tuple direction = tuple_make_vector(0.0, 0.0, 1.0);
    Ray r = ray_make(origin, direction);
    Sphere s = sphere_make();

    Intersect xs = ray_intersect(&s, r);

    assert_int_equal(xs.count, 0);
}

static void originates_in_a_sphere(void **state)
{
    Tuple origin = tuple_make_point(0.0, 0.0, 0.0);
    Tuple direction = tuple_make_vector(0.0, 0.0, 1.0);
    Ray r = ray_make(origin, direction);
    Sphere s = sphere_make();

    Intersect xs = ray_intersect(&s, r);

    assert_int_equal(xs.count, 2);
    assert_true(utils_fequals(xs.i[0].t, -1.0));
    assert_true(utils_fequals(xs.i[1].t, 1.0));
}

static void sphere_is_behind_a_ray(void **state)
{
    Tuple origin = tuple_make_point(0.0, 0.0, 5.0);
    Tuple direction = tuple_make_vector(0.0, 0.0, 1.0);
    Ray r = ray_make(origin, direction);
    Sphere s = sphere_make();

    Intersect xs = ray_intersect(&s, r);

    assert_int_equal(xs.count, 2);
    assert_true(utils_fequals(xs.i[0].t, -6.0));
    assert_true(utils_fequals(xs.i[1].t, -4.0));
}

static void intersection_encapsulates_t_and_obj(void **state)
{
    Sphere s = sphere_make();
    Intersection i = ray_intersection(3.5, &s);

    assert_true(utils_fequals(i.t, 3.5));
    assert_ptr_equal(&s, i.object);
}

static void aggregating_intersections(void **state)
{
    Sphere s = sphere_make();
    Intersection i1 = ray_intersection(1.0, &s);
    Intersection i2 = ray_intersection(2.0, &s);

    Intersection *xs = malloc(2 * sizeof(Intersection));
    xs[0] = i1;
    xs[1] = i2;

    assert_true(utils_fequals(xs[0].t, 1.0));
    assert_true(utils_fequals(xs[1].t, 2.0)); }
static void intersect_sets_the_obj_on_intersection(void **state)
{
    Ray r = ray_make(tuple_make_point(0.0, 0.0, -5.0), 
            tuple_make_vector(0.0, 0.0, 1.0));
    Sphere s = sphere_make();
    Intersect xs = ray_intersect(&s, r);

    assert_int_equal(xs.count, 2);
    assert_ptr_equal(xs.i[0].object, &s);
    assert_ptr_equal(xs.i[1].object, &s);
}

static void hit_with_all_positive_t(void **state)
{
    Sphere s = sphere_make();
    Intersection i1 = ray_intersection(1.0, &s);
    Intersection i2 = ray_intersection(2.0, &s);

    Intersection *xs[] = { &i2, &i1 };

    Intersection *i = ray_hit(2, xs);
    assert_ptr_equal(i, &i1);
}

static void hit_with_some_negative_t(void **state)
{
    Sphere s = sphere_make();
    Intersection i1 = ray_intersection(-1.0, &s);
    Intersection i2 = ray_intersection(2.0, &s);

    Intersection *xs[] = { &i2, &i1 };

    Intersection *i = ray_hit(2, xs);
    assert_ptr_equal(i, &i2);
}

static void hit_with_all_negative_t(void **state)
{
    Sphere s = sphere_make();
    Intersection i1 = ray_intersection(-2.0, &s);
    Intersection i2 = ray_intersection(-1.0, &s);

    Intersection *xs[] = { &i2, &i1 };

    Intersection *i = ray_hit(2, xs);
    assert_ptr_equal(i, NULL);
}

static void hit_is_lowest_non_neg(void **state)
{
    Sphere s = sphere_make();
    Intersection i1 = ray_intersection(5.0, &s);
    Intersection i2 = ray_intersection(7.0, &s);
    Intersection i3 = ray_intersection(-3.0, &s);
    Intersection i4 = ray_intersection(2.0, &s);

    Intersection *xs[] = { &i1, &i2, &i3, &i4 };

    Intersection *i = ray_hit(4, xs);
    assert_ptr_equal(i, &i4);
}

static void translating_a_ray(void **state)
{
    Ray r = ray_make(tuple_make_point(1.0, 2.0, 3.0), tuple_make_vector(0.0, 1.0, 0.0));
    Matrix4 m = transform_translate(3.0, 4.0, 5.0);
    Ray r2 = ray_transform(r, m);

    assert_true(tuple_equal(r2.origin, tuple_make_point(4.0, 6.0, 8.0)));
    assert_true(tuple_equal(r2.direction, tuple_make_vector(0.0, 1.0, 0.0)));
}

static void scaling_a_ray(void **state)
{
    Ray r = ray_make(tuple_make_point(1.0, 2.0, 3.0), tuple_make_vector(0.0, 1.0, 0.0));
    Matrix4 m = transform_scale(2.0, 3.0, 4.0);
    Ray r2 = ray_transform(r, m);

    assert_true(tuple_equal(r2.origin, tuple_make_point(2.0, 6.0, 12.0)));
    assert_true(tuple_equal(r2.direction, tuple_make_vector(0.0, 3.0, 0.0)));
}

static void intersecting_a_scaled_sphere(void **state)
{
    Ray r = ray_make(tuple_make_point(0.0, 0.0, -5.0), 
            tuple_make_vector(0.0, 0.0, 1.0));
    Sphere s = sphere_make();

    sphere_set_transform(&s, transform_scale(2.0, 2.0, 2.0));
    Intersect xs = ray_intersect(&s, r);

    assert_int_equal(xs.count, 2);
    assert_true(utils_fequals(xs.i[0].t, 3.0));
    assert_true(utils_fequals(xs.i[1].t, 7.0));
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
        cmocka_unit_test(intersection_encapsulates_t_and_obj),
        cmocka_unit_test(aggregating_intersections),
        cmocka_unit_test(intersect_sets_the_obj_on_intersection),
        cmocka_unit_test(hit_with_all_positive_t),
        cmocka_unit_test(hit_with_some_negative_t),
        cmocka_unit_test(hit_with_all_negative_t),
        cmocka_unit_test(hit_is_lowest_non_neg),
        cmocka_unit_test(translating_a_ray),
        cmocka_unit_test(scaling_a_ray),
        cmocka_unit_test(intersecting_a_scaled_sphere),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
