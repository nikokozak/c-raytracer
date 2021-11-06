#ifndef RAYTRACE_MATRIX
#define RAYTRACE_MATRIX
#define MAT4_SIZE 4
#define MAT3_SIZE 3
#define MAT2_SIZE 2
#include <stdbool.h>
#include "tuple.h"

typedef struct Matrix4 {
    double m[MAT4_SIZE][MAT4_SIZE];
} Matrix4;

typedef struct Matrix3 {
    double m[MAT3_SIZE][MAT3_SIZE];
} Matrix3;

typedef struct Matrix2 {
    double m[MAT2_SIZE][MAT2_SIZE];
} Matrix2;

bool matrix4_equal(Matrix4, Matrix4);
bool matrix3_equal(Matrix3, Matrix3);
bool matrix2_equal(Matrix2, Matrix2);

Tuple matrix4_mult_tuple(Matrix4, Tuple);
Matrix4 matrix4_mult(Matrix4, Matrix4);
Matrix4 matrix4_identity(void);
Matrix4 matrix4_transpose(Matrix4);

double matrix2_determinant(Matrix2);
Matrix2 matrix3_submatrix(Matrix3, int, int);
Matrix3 matrix4_submatrix(Matrix4, int, int);
double matrix3_minor(Matrix3, int, int);
double matrix3_cofactor(Matrix3, int, int);
double matrix4_minor(Matrix4, int, int);
double matrix4_cofactor(Matrix4, int, int);
double matrix3_determinant(Matrix3);
double matrix4_determinant(Matrix4);

bool matrix4_invertible(Matrix4);
Matrix4 matrix4_inverse(Matrix4);
#endif
