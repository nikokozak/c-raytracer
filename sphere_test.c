#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <math.h>
#include <stdio.h>
#include "ray.h"
#include "transform.h"
#include "sphere.h"
#include "utils.h"

static void sphere_default_transformation(void **state)
{
    Sphere s = sphere_make();

    assert_true(matrix4_equal(s.transform, matrix4_identity()));
}

static void set_sphere_transformation(void **state)
{
    Sphere s = sphere_make();
    Matrix4 t = transform_translate(2.0, 3.0, 4.0);

    sphere_set_transform(&s, t);

    assert_true(matrix4_equal(s.transform, t));
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(sphere_default_transformation),
        cmocka_unit_test(set_sphere_transformation),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
