#include "color.h"

Color color_make(double red, double blue, double green)
{
    return (Color) { red, blue, green };
}

Color color_add(Color a, Color b)
{
    return (Color) { a.red + b.red,
        a.green + b.green,
        a.blue + b.blue };
}

Color color_sub(Color a, Color b)
{
    return (Color) { a.red - b.red,
        a.green - b.green,
        a.blue - b.blue };
}

Color color_mult(Color a, Color b)
{
    return (Color) { a.red * b.red,
        a.green * b.green,
        a.blue * b.blue };
}

Color color_scale(Color a, double s)
{
    return (Color) { a.red * s,
        a.green * s,
        a.blue * s };
}

int color_to_255(double channel)
{
    channel = 255.0 * channel;
    const double t = channel < 0.0 ? 0.0 : channel;
    return (int) t > 255.0 ? 255.0 : t;
}
