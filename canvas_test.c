#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <math.h>
#include "canvas.h"
#include "utils.h"

static void makes_canvas(void **state)
{
    Canvas *c = canvas_make(10, 20);

    assert_int_equal(c->width, 10);
    assert_int_equal(c->height, 20);

    for (int i = 0; i < c->width * c->height; i++)
    {
        assert_true(utils_fequals(c->pixels[i].red, 0.0));
        assert_true(utils_fequals(c->pixels[i].green, 0.0));
        assert_true(utils_fequals(c->pixels[i].blue, 0.0));
    }
}

static void writes_pixels(void **state)
{
    Canvas *c = canvas_make(10, 20);
    Color r = color_make(1.0, 0.0, 0.0);

    canvas_write_pixel(c, 2, 3, r);

    Color pixel = c->pixels[canvas_pixel_index_at(c, 2, 3)];

    assert_int_equal(pixel.red, 1.0);
    assert_int_equal(pixel.green, 0.0);
    assert_int_equal(pixel.blue, 0.0);
}

static void creates_correct_header(void **state)
{
    Canvas *c = canvas_make(5, 3);
    char* header = canvas_ppm_header(c);
    assert_string_equal("P3\n5 3\n255\n", header);
}

static void creates_correct_body(void **state)
{
    Canvas *c = canvas_make(1, 1);
    char *cbody = canvas_ppm_body(c);
    assert_string_equal("0 0 0 ", cbody);

    Canvas *b = canvas_make(2, 1);
    canvas_write_pixel(b, 0, 1, color_make(1.0, 0.0, 0.0));
    char *bbody = canvas_ppm_body(b);
    assert_string_equal("0 0 0 255 0 0 ", bbody);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(makes_canvas),
        cmocka_unit_test(writes_pixels),
        cmocka_unit_test(creates_correct_header),
        cmocka_unit_test(creates_correct_body)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
