#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "tuple.h"

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
