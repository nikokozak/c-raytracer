#ifndef RAYTRACE_COLOR
#define RAYTRACE_COLOR

typedef struct Color {
    double red;
    double green;
    double blue;
} Color;

Color color_make(double, double, double);
Color color_add(Color, Color);
Color color_sub(Color, Color);
Color color_mult(Color, Color);
Color color_scale(Color, double);

int color_to_255(double);

#endif
