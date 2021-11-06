#include <stdio.h>
#include "tuple.h"
#include "color.h"
#include "canvas.h"
#include "transform.h"
#include "matrix.h"

Canvas *c;
Tuple center_point;

int Width = 200;
int Height = 200;
double Radius = 50.0;

int main(void)
{
    FILE *fp = fopen("pic.ppm", "w");
    c = canvas_make(Width, Height);
    center_point = tuple_make_point(((double) Width) / 2.0, ((double) Height) / 2.0, 0.0);
    
    for (int i = 0; i <= 12; i++) {
       Tuple curr_point = tuple_make_point(0.0, 1.0, 0.0);
       Matrix4 rotation = transform_rotate_z(i * (M_PI / 6.0));
       Tuple rotated_point = matrix4_mult_tuple(rotation, curr_point);

       double final_x = (rotated_point.x * Radius) + center_point.x;
       double final_y = (rotated_point.y * Radius) + center_point.y;

       printf("%f, %f\n", final_x, final_y);

       canvas_write_pixel(c, final_x, final_y, color_make(1.0, 0.0, 0.0));
    }

    fputs(canvas_to_ppm(c), fp);
    fclose(fp);
}
