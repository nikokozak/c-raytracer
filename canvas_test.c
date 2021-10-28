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

    Color pixel = canvas_pixel_at(c, 2, 3);

    assert_int_equal(pixel.red, 1.0);
    assert_int_equal(pixel.green, 0.0);
    assert_int_equal(pixel.blue, 0.0);
}

static void creates_correct_ppm_header(void **state)
{
    Canvas *c = canvas_make(5, 3);
    char* header = canvas_ppm_header(c);
    assert_string_equal("P3\n5 3\n255\n", header);
}

static void creates_correct_ppm_body(void **state)
{
    Canvas *c = canvas_make(1, 1);
    char *cbody = canvas_ppm_body(c);
    assert_string_equal("0 0 0\n", cbody);

    Canvas *b = canvas_make(2, 1);
    canvas_write_pixel(b, 1, 0, color_make(1.0, 0.0, 0.0));
    char *bbody = canvas_ppm_body(b);
    assert_string_equal("0 0 0 255 0 0\n", bbody);
}

static void creates_correct_ppm(void **state)
{
    Canvas *c = canvas_make(5, 3);
    Color c1 = color_make(1.5, 0.0, 0.0);
    Color c2 = color_make(0.0, 0.5, 0.0);
    Color c3 = color_make(-0.5, 0.0, 1.0);

    canvas_write_pixel(c, 0, 0, c1);
    canvas_write_pixel(c, 2, 1, c2);
    canvas_write_pixel(c, 4, 2, c3);

    char *ppm = canvas_to_ppm(c);

    char *expected_result = 
        "P3\n5 3\n255\n"
        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 127 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";

    assert_string_equal(expected_result, ppm);
}

static void splits_ppm_long_lines(void **state)
{
    Canvas *c = canvas_make(10, 2);
    for (int i = 0; i < c->width * c->height; i++)
    {
        c->pixels[i] = color_make(1.0, 0.8, 0.6);
    }

    char *ppm = canvas_to_ppm(c);

    char *expected_result = 
        "P3\n10 2\n255\n"
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 153"

        "0 0 0 0 0 0 0 127 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";

    assert_string_equal(expected_result, ppm);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(makes_canvas),
        cmocka_unit_test(writes_pixels),
        cmocka_unit_test(creates_correct_ppm_header),
        cmocka_unit_test(creates_correct_ppm_body),
        cmocka_unit_test(creates_correct_ppm),
        cmocka_unit_test(splits_ppm_long_lines)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
