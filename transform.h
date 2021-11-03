#include "matrix.h"
#include "math.h"

Matrix4 transform_translation(double x, double y, double z);
Matrix4 transform_scale(double x, double y, double z);
Matrix4 transform_rotate_x(double radians);
Matrix4 transform_rotate_y(double radians);
Matrix4 transform_rotate_z(double radians);
Matrix4 transform_shear(double xy, double xz, double yx, double yz, double zx, double zy);

