#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <math.h>
#include "tuple.h"
#include "utils.h"

static void a_tuple_is_a_point(void **state)
{
    Tuple tup = tuple_make_tuple(4.3, -4.2, 3.1, 1.0);

    assert_true(tuple_is_point(tup));
    assert_false(tuple_is_vector(tup));
}

static void a_tuple_is_a_vector(void **state)
{
    Tuple tup = tuple_make_tuple(4.3, -4.2, 3.1, 0.0);

    assert_true(tuple_is_vector(tup));
    assert_false(tuple_is_point(tup));
}

static void make_point_makes_point(void **state)
{
    Tuple tup = tuple_make_point(4.3, -4.2, 3.1);

    assert_true(tuple_is_point(tup));
    assert_false(tuple_is_vector(tup));
}

static void make_vector_makes_vector(void **state)
{
    Tuple tup = tuple_make_vector(4.3, -4.2, 3.1);

    assert_true(tuple_is_vector(tup));
    assert_false(tuple_is_point(tup));
}

static void adding_point_and_vector(void **state)
{
    Tuple a = tuple_make_point(3.0, -2.0, 5.0);
    Tuple b = tuple_make_vector(-2.0, 3.0, 1.0);

    Tuple result = tuple_add(a, b);

    assert_true(utils_fequals(result.x, 1.0));
    assert_true(utils_fequals(result.y, 1.0));
    assert_true(utils_fequals(result.z, 6.0));
    assert_true(utils_fequals(result.w, 1.0));
}

static void subtracting_two_points(void **state)
{
    Tuple a = tuple_make_point(3.0, 2.0, 1.0);
    Tuple b = tuple_make_point(5.0, 6.0, 7.0);

    Tuple result = tuple_sub(a, b);

    assert_true(utils_fequals(result.x, -2.0));
    assert_true(utils_fequals(result.y, -4.0));
    assert_true(utils_fequals(result.z, -6.0));
    assert_true(utils_fequals(result.w, 0.0));
}

static void subtracting_vector_from_point(void **state)
{
    Tuple a = tuple_make_point(3.0, 2.0, 1.0);
    Tuple b = tuple_make_vector(5.0, 6.0, 7.0);

    Tuple result = tuple_sub(a, b);

    assert_true(utils_fequals(result.x, -2.0));
    assert_true(utils_fequals(result.y, -4.0));
    assert_true(utils_fequals(result.z, -6.0));
    assert_true(utils_fequals(result.w, 1.0));
}

static void subtracting_two_vectors(void **state)
{
    Tuple a = tuple_make_vector(3.0, 2.0, 1.0);
    Tuple b = tuple_make_vector(5.0, 6.0, 7.0);

    Tuple result = tuple_sub(a, b);

    assert_true(utils_fequals(result.x, -2.0));
    assert_true(utils_fequals(result.y, -4.0));
    assert_true(utils_fequals(result.z, -6.0));
    assert_true(utils_fequals(result.w, 0.0));
}

static void negating_a_tuple(void **state)
{
    Tuple a = tuple_make_tuple(1.0, -2.0, 3.0, -4.0);

    Tuple result = tuple_negate(a);

    assert_true(utils_fequals(result.x, -1.0));
    assert_true(utils_fequals(result.y, 2.0));
    assert_true(utils_fequals(result.z, -3.0));
    assert_true(utils_fequals(result.w, 4.0));
}

static void multiplying_tuple_by_scalar(void **state)
{
    Tuple a = tuple_make_tuple(1.0, -2.0, 3.0, -4.0);

    Tuple result = tuple_mult(a, 3.5);

    assert_true(utils_fequals(result.x, 3.5));
    assert_true(utils_fequals(result.y, -7.0));
    assert_true(utils_fequals(result.z, 10.5));
    assert_true(utils_fequals(result.w, -14.0));
}

static void multiplying_tuple_by_fraction(void **state)
{
    Tuple a = tuple_make_tuple(1.0, -2.0, 3.0, -4.0);

    Tuple result = tuple_mult(a, 0.5);

    assert_true(utils_fequals(result.x, 0.5));
    assert_true(utils_fequals(result.y, -1.0));
    assert_true(utils_fequals(result.z, 1.5));
    assert_true(utils_fequals(result.w, -2.0));
}

static void dividing_tuple_by_scalar(void **state)
{
    Tuple a = tuple_make_tuple(1.0, -2.0, 3.0, -4.0);

    Tuple result = tuple_div(a, 2.0);

    assert_true(utils_fequals(result.x, 0.5));
    assert_true(utils_fequals(result.y, -1.0));
    assert_true(utils_fequals(result.z, 1.5));
    assert_true(utils_fequals(result.w, -2.0));
}

static void computing_the_magnitude_of_vector(void **state)
{
    Tuple a = tuple_make_vector(1.0, 0.0, 0.0);
    assert_true(utils_fequals(tuple_magnitude(a), 1.0));

    Tuple b = tuple_make_vector(0.0, 1.0, 0.0);
    assert_true(utils_fequals(tuple_magnitude(b), 1.0));

    Tuple c = tuple_make_vector(0.0, 0.0, 1.0);
    assert_true(utils_fequals(tuple_magnitude(c), 1.0));

    Tuple d = tuple_make_vector(1.0, 2.0, 3.0);
    assert_true(utils_fequals(tuple_magnitude(d), sqrt(14.0)));

    Tuple e = tuple_make_vector(-1.0, -2.0, -3.0);
    assert_true(utils_fequals(tuple_magnitude(e), sqrt(14.0)));
}

static void normalizing_a_vector(void **state)
{
    Tuple a = tuple_make_vector(4.0, 0.0, 0.0);
    Tuple result_a = tuple_normalize(a);
    assert_true(utils_fequals(result_a.x, 1.0));
    assert_true(utils_fequals(result_a.y, 0.0));
    assert_true(utils_fequals(result_a.z, 0.0));
    assert_true(utils_fequals(result_a.w, 0.0));

    Tuple b = tuple_make_vector(1.0, 2.0, 3.0);
    Tuple result_b = tuple_normalize(b);
    assert_true(utils_fequals(result_b.x, 1.0 / sqrt(14)));
    assert_true(utils_fequals(result_b.y, 2.0 / sqrt(14)));
    assert_true(utils_fequals(result_b.z, 3.0 / sqrt(14)));
    assert_true(utils_fequals(result_b.w, 0.0));
}

static void magnitude_of_normalized_vector(void **state)
{
    Tuple a = tuple_make_vector(1.0, 2.0, 3.0);
    Tuple normalized = tuple_normalize(a);

    assert_true(utils_fequals(tuple_magnitude(normalized), 1.0));
}

static void dot_product(void **state)
{
    Tuple a = tuple_make_vector(1.0, 2.0, 3.0);
    Tuple b = tuple_make_vector(2.0, 3.0, 4.0);

    assert_true(utils_fequals(tuple_dot(a, b), 20.0));
}

static void cross_product(void **state)
{
    Tuple a = tuple_make_vector(1.0, 2.0, 3.0);
    Tuple b = tuple_make_vector(2.0, 3.0, 4.0);

    Tuple cross_a_b = tuple_cross(a, b);
    Tuple cross_b_a = tuple_cross(b, a);

    assert_true(utils_fequals(cross_a_b.x, -1.0));
    assert_true(utils_fequals(cross_a_b.y, 2.0));
    assert_true(utils_fequals(cross_a_b.z, -1.0));
    assert_true(utils_fequals(cross_b_a.x, 1.0));
    assert_true(utils_fequals(cross_b_a.y, -2.0));
    assert_true(utils_fequals(cross_b_a.z, 1.0));
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(a_tuple_is_a_point),
        cmocka_unit_test(a_tuple_is_a_vector),
        cmocka_unit_test(make_point_makes_point),
        cmocka_unit_test(make_vector_makes_vector),
        cmocka_unit_test(adding_point_and_vector),
        cmocka_unit_test(subtracting_two_points),
        cmocka_unit_test(subtracting_vector_from_point),
        cmocka_unit_test(subtracting_two_vectors),
        cmocka_unit_test(negating_a_tuple),
        cmocka_unit_test(multiplying_tuple_by_scalar),
        cmocka_unit_test(multiplying_tuple_by_fraction),
        cmocka_unit_test(dividing_tuple_by_scalar),
        cmocka_unit_test(computing_the_magnitude_of_vector),
        cmocka_unit_test(normalizing_a_vector),
        cmocka_unit_test(magnitude_of_normalized_vector),
        cmocka_unit_test(dot_product),
        cmocka_unit_test(cross_product)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
