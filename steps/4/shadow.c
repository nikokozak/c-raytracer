#include <stdio.h>
#include "ray.h"
#include "color.h"
#include "canvas.h"
#include "transform.h"

Canvas *c;
Color col;
Sphere shape;
int y, x;
double world_y, world_x, pixel_size, half;
Tuple position;
Ray r; 
Intersect xs;

double canvas_pixels = 200;
double wall_z = 10.0;
double wall_size = 7.0;

int main(void)
{
    FILE *fp = fopen("pic.ppm", "w");
    c = canvas_make(canvas_pixels, canvas_pixels);
    col = color_make(1.0, 0.0, 0.0);
    shape = sphere_make();
    pixel_size = wall_size / canvas_pixels;
    half = wall_size / 2.0;

    // sphere_set_transform(&shape, transform_scale(1.0, 0.5, 1.0));
    // sphere_set_transform(&shape, transform_scale(0.5, 1.0, 1.0));
    // sphere_set_transform(&shape, transform_rotate_z(M_PI/4.0) * transform_scale(0.5, 1.0, 1.0));
    // sphere_set_transform(&shape, transform_shear(1.0, 0.0, 0.0, 0.0, 0.0, 0.0) * transform_scale(0.5, 1.0, 1.0));

    Tuple ray_origin = tuple_make_point(0.0, 0.0, -5.0);

    for (y = 0; y < canvas_pixels; y++) {
        world_y = half - pixel_size * y;
        for (x = 0; x < canvas_pixels; x++) {
            world_x = -half + pixel_size * x;
            position = tuple_make_point(world_x, world_y, wall_z);
            r = ray_make(ray_origin, tuple_normalize(tuple_sub(position, ray_origin)));
            xs = ray_intersect(&shape, r);
            // TODO: Refine this, feels clunky.
            Intersection *is[] = { &xs.i[0], &xs.i[1] };

            if (ray_hit(2, is) != NULL) {
                canvas_write_pixel(c, x, y, col);
            }
        }
    }

    fputs(canvas_to_ppm(c), fp);
    fclose(fp);
}
