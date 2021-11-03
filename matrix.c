#include "matrix.h"
#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

bool matrix4_equal(Matrix4 a, Matrix4 b)
{
    for (int row = 0; row < MAT4_SIZE; row++)
    {
        for (int col = 0; col < MAT4_SIZE; col++)
        {
            bool equal = utils_fequals(a.m[row][col], b.m[row][col]);

            if (!equal) { return false; }
        }
    }
    return true;
}

bool matrix3_equal(Matrix3 a, Matrix3 b)
{
    for (int row = 0; row < MAT3_SIZE; row++)
    {
        for (int col = 0; col < MAT3_SIZE; col++)
        {
            bool equal = utils_fequals(a.m[row][col], b.m[row][col]);

            if (!equal) { return false; }
        }
    }
    return true;
}

bool matrix2_equal(Matrix2 a, Matrix2 b)
{
    for (int row = 0; row < MAT2_SIZE; row++)
    {
        for (int col = 0; col < MAT2_SIZE; col++)
        {
            bool equal = utils_fequals(a.m[row][col], b.m[row][col]);

            if (!equal) { return false; }
        }
    }
    return true;
}

Matrix4 matrix4_mult(Matrix4 a, Matrix4 b)
{
    Matrix4 res = { 0.0 };

    for (int row = 0; row < MAT4_SIZE; row++)
    {
        for (int col = 0; col < MAT4_SIZE; col++)
        {
            res.m[row][col] = a.m[row][0] * b.m[0][col] +
                a.m[row][1] * b.m[1][col] +
                a.m[row][2] * b.m[2][col] +
                a.m[row][3] * b.m[3][col];
        }
    }

    return res;
}

Tuple matrix4_mult_tuple(Matrix4 a, Tuple t)
{
    return (Tuple) { a.m[0][0] * t.x + a.m[0][1] * t.y + a.m[0][2] * t.z + a.m[0][3] * t.w,
        a.m[1][0] * t.x + a.m[1][1] * t.y + a.m[1][2] * t.z + a.m[1][3] * t.w,
        a.m[2][0] * t.x + a.m[2][1] * t.y + a.m[2][2] * t.z + a.m[2][3] * t.w,
        a.m[3][0] * t.x + a.m[3][1] * t.y + a.m[3][2] * t.z + a.m[3][3] * t.w };
}

Matrix4 matrix4_identity(void)
{
    return (Matrix4) { 
        .m[0][0] = 1.0,
        .m[1][1] = 1.0,
        .m[2][2] = 1.0,
        .m[3][3] = 1.0
    };
}

Matrix4 matrix4_transpose(Matrix4 a)
{
    Matrix4 result = { 0.0 };
    for (int row = 0; row < MAT4_SIZE; row++) {
        for (int col = 0; col < MAT4_SIZE; col++) {
            result.m[row][col] = a.m[col][row];
        }
    }
    return result;
}

double matrix2_determinant(Matrix2 a)
{
    return a.m[0][0] * a.m[1][1] - a.m[0][1] * a.m[1][0];
}

Matrix2 matrix3_submatrix(Matrix3 a, int row_rmv, int col_rmv)
{
    Matrix2 result = { 0.0 };

    for (int row = 0, ir = 0; row < MAT3_SIZE; row++) {
        if (row_rmv == row) { continue; }

        if (row > row_rmv) { ir = row - 1; } else { ir = row; }

        for (int col = 0, ic = 0; col < MAT3_SIZE; col++) {
            if (col_rmv == col) { continue; }

            if (col > col_rmv) { ic = col - 1; } else { ic = col; }

            result.m[ir][ic] = a.m[row][col];
        }
    }

    return result;
}

Matrix3 matrix4_submatrix(Matrix4 a, int row_rmv, int col_rmv)
{
    Matrix3 result = { 0.0 };

    for (int row = 0, ir = 0; row < MAT4_SIZE; row++) {
        if (row_rmv == row) { continue; }

        if (row > row_rmv) { ir = row - 1; } else { ir = row; }

        for (int col = 0, ic = 0; col < MAT4_SIZE; col++) {
            if (col_rmv == col) { continue; }

            if (col > col_rmv) { ic = col - 1; } else { ic = col; }

            result.m[ir][ic] = a.m[row][col];
        }
    }

    return result;
}

double matrix3_minor(Matrix3 a, int row, int col)
{
    return matrix2_determinant(matrix3_submatrix(a, row, col));
}

double matrix3_cofactor(Matrix3 a, int row, int col)
{
    signed char sign = ((row + col) % 2) == 0 ? 1 : -1;

    return matrix3_minor(a, row, col) * sign;
}

double matrix4_minor(Matrix4 a, int row, int col)
{
    return matrix3_determinant(matrix4_submatrix(a, row, col));
}

double matrix4_cofactor(Matrix4 a, int row, int col)
{
    signed char sign = ((row + col) % 2) == 0 ? 1 : -1;

    return matrix4_minor(a, row, col) * sign;
}

double matrix3_determinant(Matrix3 a)
{
    double det = 0.0;
    for (int col = 0; col < MAT3_SIZE; col++)
    {
       det = det + a.m[0][col] * matrix3_cofactor(a, 0, col); 
    }
    return det;
}

double matrix4_determinant(Matrix4 a)
{
    double det = 0.0;
    for (int col = 0; col < MAT4_SIZE; col++)
    {
       det = det + a.m[0][col] * matrix4_cofactor(a, 0, col); 
    }
    return det;
}

bool matrix4_invertible(Matrix4 a)
{
    return matrix4_determinant(a) == 0 ? false : true;
}

Matrix4 matrix4_inverse(Matrix4 a)
{
    assert(matrix4_invertible(a));

    Matrix4 result = { 0.0 };

    for (int row = 0; row < MAT4_SIZE; row++) {
        for (int col = 0; col < MAT4_SIZE; col++) {
            double c = matrix4_cofactor(a, row, col);

            result.m[col][row] = c / matrix4_determinant(a);
        }
    }

    return result;
}
