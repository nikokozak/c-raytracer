#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "tuple.h"
#include "utils.h"

static void a_tuple_is_a_point(void **state)
{
    Tuple tup = tuple_make_tuple(4.3, -4.2, 3.1, 1.0);

    assert_true(tuple_is_point(&tup));
    assert_false(tuple_is_vector(&tup));
}

static void a_tuple_is_a_vector(void **state)
{
    Tuple tup = tuple_make_tuple(4.3, -4.2, 3.1, 0.0);

    assert_true(tuple_is_vector(&tup));
    assert_false(tuple_is_point(&tup));
}

static void make_point_makes_point(void **state)
{
    Tuple tup = tuple_make_point(4.3, -4.2, 3.1);

    assert_true(tuple_is_point(&tup));
    assert_false(tuple_is_vector(&tup));
}

static void make_vector_makes_vector(void **state)
{
    Tuple tup = tuple_make_vector(4.3, -4.2, 3.1);

    assert_true(tuple_is_vector(&tup));
    assert_false(tuple_is_point(&tup));
}

static void adding_two_tuples(void **state)
{
    Tuple a = tuple_make_point(3.0, -2.0, 5.0);
    Tuple b = tuple_make_vector(-2.0, 3.0, 1.0);

    Tuple result = tuple_add(&a, &b);

    assert_true(utils_fequals(result.x, 1.0));
    assert_true(utils_fequals(result.y, 1.0));
    assert_true(utils_fequals(result.z, 6.0));
    assert_true(utils_fequals(result.w, 1.0));
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(a_tuple_is_a_point),
        cmocka_unit_test(a_tuple_is_a_vector),
        cmocka_unit_test(make_point_makes_point),
        cmocka_unit_test(make_vector_makes_vector)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
