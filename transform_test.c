#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <math.h>
#include <stdio.h>
#include "transform.h"
#include "tuple.h"
#include "utils.h"

static void translation_does_not_affect_vectors(void **state)
{
    Matrix4 transform = transform_translation(5.0, -3.0, 2.0);
    Tuple vector = tuple_make_vector(-3.0, 4.0, 5.0);

    Tuple result = matrix4_mult_tuple(transform, vector);

    assert_true(tuple_equal(result, vector));
}

static void multiplying_by_a_translation_matrix(void **state)
{
    Matrix4 transform = transform_translation(5.0, -3.0, 2.0);
    Tuple point = tuple_make_point(-3.0, 4.0, 5.0);

    Tuple result = matrix4_mult_tuple(transform, point);
    Tuple expected = tuple_make_point(2.0, 1.0, 7.0);

    assert_true(tuple_equal(result, expected));
}

static void multiplying_by_inverse_translation_matrix(void **state)
{
    Matrix4 transform = transform_translation(5.0, -3.0, 2.0);
    Matrix4 inv = matrix4_inverse(transform);
    Tuple point = tuple_make_point(-3.0, 4.0, 5.0);

    Tuple result = matrix4_mult_tuple(inv, point);
    Tuple expected = tuple_make_point(-8.0, 7.0, 3.0);

    assert_true(tuple_equal(result, expected));
}

static void scaling_applied_to_a_point(void **state)
{
    Matrix4 transform = transform_scale(2.0, 3.0, 4.0);
    Tuple point = tuple_make_point(-4.0, 6.0, 8.0);

    Tuple result = matrix4_mult_tuple(transform, point);
    Tuple expected = tuple_make_point(-8.0, 18.0, 32.0);

    assert_true(tuple_equal(result, expected));
}

static void scaling_applied_to_a_vector(void **state)
{
    Matrix4 transform = transform_scale(2.0, 3.0, 4.0);
    Tuple vector = tuple_make_vector(-4.0, 6.0, 8.0);

    Tuple result = matrix4_mult_tuple(transform, vector);
    Tuple expected = tuple_make_vector(-8.0, 18.0, 32.0);

    assert_true(tuple_equal(result, expected));
}

static void multiplying_by_inverse_of_scaling_matrix(void **state)
{
    Matrix4 transform = transform_scale(2.0, 3.0, 4.0);
    Matrix4 inv = matrix4_inverse(transform);
    Tuple vector = tuple_make_vector(-4.0, 6.0, 8.0);

    Tuple result = matrix4_mult_tuple(inv, vector);
    Tuple expected = tuple_make_vector(-2.0, 2.0, 2.0);

    assert_true(tuple_equal(result, expected));
}

static void reflecting_across_axis(void **state)
{
    Matrix4 transform = transform_scale(-1.0, 1.0, 1.0);
    Tuple point = tuple_make_point(2.0, 3.0, 4.0);

    Tuple result = matrix4_mult_tuple(transform, point);
    Tuple expected = tuple_make_point(-2.0, 3.0, 4.0);

    assert_true(tuple_equal(result, expected));
}

static void rotating_around_x_axis(void **state)
{
    Matrix4 half_quarter = transform_rotate_x(M_PI / 4);
    Matrix4 full_quarter = transform_rotate_x(M_PI / 2);
    Tuple point = tuple_make_point(0.0, 1.0, 0.0);

    Tuple hq_result = matrix4_mult_tuple(half_quarter, point);
    Tuple fq_result = matrix4_mult_tuple(full_quarter, point);
    Tuple hq_expected = tuple_make_point(0.0, sqrt(2.0) / 2.0, sqrt(2.0) / 2.0);
    Tuple fq_expected = tuple_make_point(0.0, 0.0, 1.0);

    assert_true(tuple_equal(hq_result, hq_expected));
    assert_true(tuple_equal(fq_result, fq_expected));
}

static void inverse_rotation_around_x(void **state)
{
    Matrix4 half_quarter = transform_rotate_x(M_PI / 4);
    Matrix4 inv = matrix4_inverse(half_quarter);
    Tuple point = tuple_make_point(0.0, 1.0, 0.0);

    Tuple hq_result = matrix4_mult_tuple(inv, point);
    Tuple hq_expected = tuple_make_point(0.0, sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0);

    assert_true(tuple_equal(hq_result, hq_expected));
}

static void rotating_around_y_axis(void **state)
{
    Matrix4 half_quarter = transform_rotate_y(M_PI / 4);
    Matrix4 full_quarter = transform_rotate_y(M_PI / 2);
    Tuple point = tuple_make_point(0.0, 0.0, 1.0);

    Tuple hq_result = matrix4_mult_tuple(half_quarter, point);
    Tuple fq_result = matrix4_mult_tuple(full_quarter, point);
    Tuple hq_expected = tuple_make_point(sqrt(2.0) / 2.0, 0.0, sqrt(2.0) / 2.0);
    Tuple fq_expected = tuple_make_point(1.0, 0.0, 0.0);

    assert_true(tuple_equal(hq_result, hq_expected));
    assert_true(tuple_equal(fq_result, fq_expected));
}

static void rotating_around_z_axis(void **state)
{
    Matrix4 half_quarter = transform_rotate_z(M_PI / 4);
    Matrix4 full_quarter = transform_rotate_z(M_PI / 2);
    Tuple point = tuple_make_point(0.0, 1.0, 0.0);

    Tuple hq_result = matrix4_mult_tuple(half_quarter, point);
    Tuple fq_result = matrix4_mult_tuple(full_quarter, point);
    Tuple hq_expected = tuple_make_point(-sqrt(2.0) / 2.0, sqrt(2.0) / 2.0, 0.0);
    Tuple fq_expected = tuple_make_point(-1.0, 0.0, 0.0);

    assert_true(tuple_equal(hq_result, hq_expected));
    assert_true(tuple_equal(fq_result, fq_expected));
}

static void shearing(void **state)
{
    Matrix4 xy = transform_shear(1.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    Tuple pxy = tuple_make_point(2.0, 3.0, 4.0);
    Tuple exp_pxy = tuple_make_point(5.0, 3.0, 4.0);
    Tuple res_pxy = matrix4_mult_tuple(xy, pxy);

    assert_true(tuple_equal(exp_pxy, res_pxy));

    Matrix4 xz = transform_shear(0.0, 1.0, 0.0, 0.0, 0.0, 0.0);
    Tuple pxz = tuple_make_point(2.0, 3.0, 4.0);
    Tuple exp_pxz = tuple_make_point(6.0, 3.0, 4.0);
    Tuple res_pxz = matrix4_mult_tuple(xz, pxz);

    assert_true(tuple_equal(exp_pxz, res_pxz));

    Matrix4 yx = transform_shear(0.0, 0.0, 1.0, 0.0, 0.0, 0.0);
    Tuple pyx = tuple_make_point(2.0, 3.0, 4.0);
    Tuple exp_pyx = tuple_make_point(2.0, 5.0, 4.0);
    Tuple res_pyx = matrix4_mult_tuple(yx, pyx);

    assert_true(tuple_equal(exp_pyx, res_pyx));

    Matrix4 yz = transform_shear(0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    Tuple pyz = tuple_make_point(2.0, 3.0, 4.0);
    Tuple exp_pyz = tuple_make_point(2.0, 7.0, 4.0);
    Tuple res_pyz = matrix4_mult_tuple(yz, pyz);

    assert_true(tuple_equal(exp_pyz, res_pyz));

    Matrix4 zx = transform_shear(0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    Tuple pzx = tuple_make_point(2.0, 3.0, 4.0);
    Tuple exp_pzx = tuple_make_point(2.0, 3.0, 6.0);
    Tuple res_pzx = matrix4_mult_tuple(zx, pzx);

    assert_true(tuple_equal(exp_pzx, res_pzx));

    Matrix4 zy = transform_shear(0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    Tuple pzy = tuple_make_point(2.0, 3.0, 4.0);
    Tuple exp_pzy = tuple_make_point(2.0, 3.0, 7.0);
    Tuple res_pzy = matrix4_mult_tuple(zy, pzy);

    assert_true(tuple_equal(exp_pzy, res_pzy));
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(translation_does_not_affect_vectors),
        cmocka_unit_test(multiplying_by_a_translation_matrix),
        cmocka_unit_test(multiplying_by_inverse_translation_matrix),
        cmocka_unit_test(scaling_applied_to_a_point),
        cmocka_unit_test(scaling_applied_to_a_vector),
        cmocka_unit_test(multiplying_by_inverse_translation_matrix),
        cmocka_unit_test(reflecting_across_axis),
        cmocka_unit_test(rotating_around_x_axis),
        cmocka_unit_test(inverse_rotation_around_x),
        cmocka_unit_test(rotating_around_y_axis),
        cmocka_unit_test(rotating_around_z_axis),
        cmocka_unit_test(shearing),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
