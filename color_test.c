#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <math.h>
#include "color.h"
#include "utils.h"

static void makes_color(void **state)
{
    Color a = color_make(-0.5, 0.4, 1.7);

    assert_true(utils_fequals(a.red, -0.5));
    assert_true(utils_fequals(a.green, 0.4));
    assert_true(utils_fequals(a.blue, 1.7));
}

static void adds_color(void **state)
{
    Color a = color_make(0.9, 0.6, 0.75);
    Color b = color_make(0.7, 0.1, 0.25);

    Color result = color_add(a, b);

    assert_true(utils_fequals(result.red, 1.6));
    assert_true(utils_fequals(result.green, 0.7));
    assert_true(utils_fequals(result.blue, 1.0));
}

static void subtracts_color(void **state)
{
    Color a = color_make(0.9, 0.6, 0.75);
    Color b = color_make(0.7, 0.1, 0.25);

    Color result = color_sub(a, b);

    assert_true(utils_fequals(result.red, 0.2));
    assert_true(utils_fequals(result.green, 0.5));
    assert_true(utils_fequals(result.blue, 0.5));
}

static void multiplies_color_by_scalar(void **state)
{
    Color a = color_make(0.2, 0.3, 0.4);

    Color result = color_scale(a, 2.0);

    assert_true(utils_fequals(result.red, 0.4));
    assert_true(utils_fequals(result.green, 0.6));
    assert_true(utils_fequals(result.blue, 0.8));
}

static void multiplies_color_by_color(void **state)
{
    Color a = color_make(1.0, 0.2, 0.4);
    Color b = color_make(0.9, 1.0, 0.1);

    Color result = color_mult(a, b);

    assert_true(utils_fequals(result.red, 0.9));
    assert_true(utils_fequals(result.green, 0.2));
    assert_true(utils_fequals(result.blue, 0.04));
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(makes_color),
        cmocka_unit_test(adds_color),
        cmocka_unit_test(subtracts_color),
        cmocka_unit_test(multiplies_color_by_scalar),
        cmocka_unit_test(multiplies_color_by_color)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
