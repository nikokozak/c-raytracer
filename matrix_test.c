#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <math.h>
#include <stdio.h>
#include "matrix.h"
#include "utils.h"

static void makes_a_4x4_matrix(void **state)
{
    Matrix4 mat = { 
        1.0, 2.0, 3.0, 4.0,
        5.5, 6.5, 7.5, 8.5,
        9.0, 10.0, 11.0, 12.0,
        13.5, 14.5, 15.5, 16.5
    };

    assert_true(utils_fequals(mat.m[0][0], 1.0));
    assert_true(utils_fequals(mat.m[0][3], 4.0));
    assert_true(utils_fequals(mat.m[1][0], 5.5));
    assert_true(utils_fequals(mat.m[1][2], 7.5));
    assert_true(utils_fequals(mat.m[2][2], 11.0));
    assert_true(utils_fequals(mat.m[3][0], 13.5));
    assert_true(utils_fequals(mat.m[3][2], 15.5));
}

static void makes_a_3x3_matrix(void **state)
{
    Matrix3 mat = { 
        -3.0, 5.0, 0.0,
        1.0, -2.0, -7.0,
        0.0, 1.0, 1.0
    };

    assert_true(utils_fequals(mat.m[0][0], -3.0));
    assert_true(utils_fequals(mat.m[1][1], -2.0));
    assert_true(utils_fequals(mat.m[2][2], 1.0));
}

static void makes_a_2x2_matrix(void **state)
{
    Matrix2 mat = { 
        -3.0, 5.0,
        1.0, -2.0
    };

    assert_true(utils_fequals(mat.m[0][0], -3.0));
    assert_true(utils_fequals(mat.m[0][1], 5.0));
    assert_true(utils_fequals(mat.m[1][0], 1.0));
    assert_true(utils_fequals(mat.m[1][1], -2.0));
}

static void matrix4_equal_is_correct(void **state)
{
    Matrix4 a = {
        1.0, 2.0, 3.0, 4.0,
        5.0, 6.0, 7.0, 8.0,
        9.0, 8.0, 7.0, 6.0,
        5.0, 4.0, 3.0, 2.0
    };

    Matrix4 b = {
        1.0, 2.0, 3.0, 4.0,
        5.0, 6.0, 7.0, 8.0,
        9.0, 8.0, 7.0, 6.0,
        5.0, 4.0, 3.0, 2.0
    };

    Matrix4 c = {
        1.0, 2.0, 3.0, 4.0,
        5.0, 6.0, 7.0, 0.0,
        9.0, 8.0, 7.0, 6.0,
        5.0, 4.0, 3.0, 2.0
    };

    assert_true(matrix4_equal(a, b));
    assert_false(matrix4_equal(a, c));
}

static void matrix4_multiplies_correctly(void **state)
{
    Matrix4 a = {
        1.0, 2.0, 3.0, 4.0,
        5.0, 6.0, 7.0, 8.0,
        9.0, 8.0, 7.0, 6.0,
        5.0, 4.0, 3.0, 2.0
    };

    Matrix4 b = {
        -2.0, 1.0, 2.0, 3.0,
        3.0, 2.0, 1.0, -1.0,
        4.0, 3.0, 6.0, 5.0,
        1.0, 2.0, 7.0, 8.0
    };

    Matrix4 expected = {
        20.0, 22.0, 50.0, 48.0,
        44.0, 54.0, 114.0, 108.0,
        40.0, 58.0, 110.0, 102.0,
        16.0, 26.0, 46.0, 42.0
    };

    Matrix4 result = matrix4_mult(a, b);

    assert_true(matrix4_equal(result, expected));
}

static void matrix4_multiplies_tuple_correctly(void **state)
{
    Matrix4 a = {
        1.0, 2.0, 3.0, 4.0,
        2.0, 4.0, 4.0, 2.0,
        8.0, 6.0, 4.0, 1.0,
        0.0, 0.0, 0.0, 1.0
    };

    Tuple b = tuple_make_tuple(1.0, 2.0, 3.0, 1.0);
    Tuple expected = tuple_make_tuple(18.0, 24.0, 33.0, 1.0);

    Tuple res = matrix4_mult_tuple(a, b);

    assert_true(utils_fequals(res.x, expected.x));
    assert_true(utils_fequals(res.y, expected.y));
    assert_true(utils_fequals(res.z, expected.z));
    assert_true(utils_fequals(res.w, expected.w));
}

static void multing_by_identity_returns_same(void **state)
{
    Matrix4 a = {
        1.0, 2.0, 3.0, 4.0,
        2.0, 4.0, 4.0, 2.0,
        8.0, 6.0, 4.0, 1.0,
        0.0, 0.0, 0.0, 1.0
    };

    Matrix4 res = matrix4_mult(matrix4_identity(), a);

    assert_true(matrix4_equal(res, a));
}

static void multing_by_identity_tuple_returns_same(void **state)
{
    Tuple a = tuple_make_tuple(1.0, 2.0, 3.0, 4.0);

    Tuple res = matrix4_mult_tuple(matrix4_identity(), a);

    assert_true(utils_fequals(res.x, a.x));
    assert_true(utils_fequals(res.y, a.y));
    assert_true(utils_fequals(res.z, a.z));
    assert_true(utils_fequals(res.w, a.w));
}

static void transposes_a_matrix(void **state)
{
    Matrix4 a = {
        0.0, 9.0, 3.0, 0.0,
        9.0, 8.0, 0.0, 8.0,
        1.0, 8.0, 5.0, 3.0,
        0.0, 0.0, 5.0, 8.0
    };

    Matrix4 expected = {
        0.0, 9.0, 1.0, 0.0,
        9.0, 8.0, 8.0, 0.0,
        3.0, 0.0, 5.0, 5.0,
        0.0, 8.0, 3.0, 8.0
    };

    Matrix4 result = matrix4_transpose(a);

    assert_true(matrix4_equal(result, expected));
}

static void transposes_identity_matrix(void **state)
{
    Matrix4 result = matrix4_transpose(matrix4_identity());

    assert_true(matrix4_equal(result, matrix4_identity()));
}

static void determinant_of_2x2_matrix(void **state)
{
    Matrix2 a = {
        1.0, 5.0,
        -3.0, 2.0
    };
    
    double expected = 17.0;

    assert_true(utils_fequals(matrix2_determinant(a), expected));
}

static void submatrix_of_a_3x3_matrix(void **state)
{
    Matrix3 a = {
        1.0, 5.0, 0.0,
        -3.0, 2.0, 7.0,
        0.0, 6.0, -3.0
    };

    Matrix2 expected = {
        -3.0, 2.0,
        0.0, 6.0
    };

    Matrix2 result = matrix3_submatrix(a, 0, 2);

    assert_true(matrix2_equal(expected, result));
}

static void submatrix_of_a_4x4_matrix(void **state)
{
    Matrix4 a = {
        -6.0, 1.0, 1.0, 6.0,
        -8.0, 5.0, 8.0, 6.0,
        -1.0, 0.0, 8.0, 2.0,
        -7.0, 1.0, -1.0, 1.0
    };

    Matrix3 expected = {
        -6.0, 1.0, 6.0,
        -8.0, 8.0, 6.0,
        -7.0, -1.0, 1.0
    };

    Matrix3 result = matrix4_submatrix(a, 2, 1);

    assert_true(matrix3_equal(expected, result));
}

static void minor_of_3x3_matrix(void **state)
{
    Matrix3 a = {
        3.0, 5.0, 0.0,
        2.0, -1.0, -7.0,
        6.0, -1.0, 5.0
    };

    double result = matrix3_minor(a, 1, 0);
    double expected = 25.0;

    assert_true(utils_fequals(result, expected));
}

static void cofactor_of_3x3_matrix(void **state)
{
    Matrix3 a = {
        3.0, 5.0, 0.0,
        2.0, -1.0, -7.0,
        6.0, -1.0, 5.0
    };

    double result_1 = matrix3_cofactor(a, 0, 0);
    double expected_1 = -12.0;
    double result_2 = matrix3_cofactor(a, 1, 0);
    double expected_2 = -25.0;

    assert_true(utils_fequals(result_1, expected_1));
    assert_true(utils_fequals(result_2, expected_2));
}

static void determinant_of_3x3_matrix(void **state)
{
    Matrix3 a = {
        1.0, 2.0, 6.0,
        -5.0, 8.0, -4.0,
        2.0, 6.0, 4.0
    };

    double result = matrix3_determinant(a);
    double expected = -196.0;

    assert_true(utils_fequals(result, expected));
}

static void determinant_of_4x4_matrix(void **state)
{
    Matrix4 a = {
        -2.0, -8.0, 3.0, 5.0,
        -3.0, 1.0, 7.0, 3.0,
        1.0, 2.0, -9.0, 6.0,
        -6.0, 7.0, 7.0, -9.0
    };

    double result = matrix4_determinant(a);
    double expected = -4071.0;

    assert_true(utils_fequals(result, expected));
}

static void invertible_4x4_test(void **state)
{
    Matrix4 a = {
        6.0, 4.0, 4.0, 4.0,
        5.0, 5.0, 7.0, 6.0,
        4.0, -9.0, 3.0, -7.0,
        9.0, 1.0, 7.0, -6.0
    };

    assert_true(matrix4_invertible(a));
}

static void noninvertible_4x4_test(void **state)
{
    Matrix4 a = {
        -4.0, 2.0, -2.0, -3.0,
        9.0, 6.0, 2.0, 6.0,
        0.0, -5.0, 1.0, -5.0,
        0.0, 0.0, 0.0, 0.0
    };

    assert_false(matrix4_invertible(a));
}

static void inverse_of_4x4_matrix(void **state)
{
    Matrix4 a = {
        8.0, -5.0, 9.0, 2.0,
        7.0, 5.0, 6.0, 1.0,
        -6.0, 0.0, 9.0, 6.0,
        -3.0, 0.0, -9.0, -4.0
    };

    Matrix4 expected = {
        -0.15385, -0.15385, -0.28205, -0.53846,
        -0.07692, 0.12308, 0.02564, 0.03077,
        0.35897, 0.35897, 0.43590, 0.92308,
        -0.69231, -0.69231, -0.76923, -1.92308
    };

    Matrix4 b = {
        9.0, 3.0, 0.0, 9.0,
        -5.0, -2.0, -6.0, -3.0,
        -4.0, 9.0, 6.0, 4.0,
        -7.0, 6.0, 6.0, 2.0
    };

    Matrix4 expected_b = {
        -0.04074, -0.07778, 0.14444, -0.22222,
        -0.07778, 0.03333, 0.36667, -0.33333,
        -0.02901, -0.14630, -0.10926, 0.12963,
        0.17778, 0.06667, -0.26667, 0.33333
    };

    assert_true(matrix4_equal(matrix4_inverse(a), expected));
    assert_true(matrix4_equal(matrix4_inverse(b), expected_b));
}

static void multiplying_product_by_inverse(void **state)
{
    Matrix4 a = {
        -3.0, -9.0, 7.0, 3.0,
        3.0, -8.0, 2.0, -9.0,
        -4.0, 4.0, 4.0, 1.0,
        -6.0, 5.0, -1.0, 1.0
    };

    Matrix4 b = {
        8.0, 2.0, 2.0, 2.0,
        3.0, -1.0, 7.0, 0.0,
        7.0, 0.0, 5.0, 4.0,
        6.0, -2.0, 0.0, 5.0
    };

    Matrix4 c = matrix4_mult(a, b);
    Matrix4 result = matrix4_mult(c, matrix4_inverse(b));

    assert_true(matrix4_equal(a, result));
}


int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(makes_a_4x4_matrix),
        cmocka_unit_test(makes_a_3x3_matrix),
        cmocka_unit_test(makes_a_2x2_matrix),
        cmocka_unit_test(matrix4_equal_is_correct),
        cmocka_unit_test(matrix4_multiplies_correctly),
        cmocka_unit_test(matrix4_multiplies_tuple_correctly),
        cmocka_unit_test(multing_by_identity_returns_same),
        cmocka_unit_test(multing_by_identity_tuple_returns_same),
        cmocka_unit_test(transposes_a_matrix),
        cmocka_unit_test(transposes_identity_matrix),
        cmocka_unit_test(submatrix_of_a_3x3_matrix),
        cmocka_unit_test(submatrix_of_a_4x4_matrix),
        cmocka_unit_test(minor_of_3x3_matrix),
        cmocka_unit_test(cofactor_of_3x3_matrix),
        cmocka_unit_test(determinant_of_2x2_matrix),
        cmocka_unit_test(determinant_of_3x3_matrix),
        cmocka_unit_test(determinant_of_4x4_matrix),
        cmocka_unit_test(noninvertible_4x4_test),
        cmocka_unit_test(invertible_4x4_test),
        cmocka_unit_test(inverse_of_4x4_matrix),
        cmocka_unit_test(multiplying_product_by_inverse),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
