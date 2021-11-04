#include "transform.h"

Matrix4 transform_translate(double x, double y, double z)
{
    Matrix4 result = matrix4_identity();
    result.m[0][3] = x;
    result.m[1][3] = y;
    result.m[2][3] = z;

    return result;
}

Matrix4 transform_scale(double x, double y, double z)
{
    Matrix4 result = matrix4_identity();
    result.m[0][0] = x;
    result.m[1][1] = y;
    result.m[2][2] = z;

    return result;
}

Matrix4 transform_rotate_x(double radians)
{
    Matrix4 result = matrix4_identity();
    result.m[1][1] = cos(radians);
    result.m[1][2] = -sin(radians);
    result.m[2][1] = sin(radians);
    result.m[2][2] = cos(radians);
    return result;
}

Matrix4 transform_rotate_y(double radians)
{
    Matrix4 result = matrix4_identity();
    result.m[0][0] = cos(radians);
    result.m[0][2] = sin(radians);
    result.m[2][0] = -sin(radians);
    result.m[2][2] = cos(radians);
    return result;
}

Matrix4 transform_rotate_z(double radians)
{
    Matrix4 result = matrix4_identity();
    result.m[0][0] = cos(radians);
    result.m[0][1] = -sin(radians);
    result.m[1][0] = sin(radians);
    result.m[1][1] = cos(radians);
    return result;
}

Matrix4 transform_shear(double xy, double xz, double yx, double yz, double zx, double zy)
{
    Matrix4 result = matrix4_identity();
    result.m[0][1] = xy;
    result.m[0][2] = xz;
    result.m[1][0] = yx;
    result.m[1][2] = yz;
    result.m[2][0] = zx;
    result.m[2][1] = zy;
    return result;
}
