#include <stdlib.h>
#include <stdio.h>
#include "color.h"
#include "utils.h"

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

int color_channel_to_255(double channel)
{
    channel = 255.0 * channel;
    return utils_clamp(channel, 0.0, 255.0);
}

char *color_channel_to_s(double channel) // Takes 0.0-1.0 scale channel
{
    char *b = (char*)malloc(3 * sizeof(char));
    sprintf(b, "%d", color_channel_to_255(channel));
    return b;
}

char *color_to_s(Color c)
{
    char *b = (char*)malloc(11 * sizeof(char));
    sprintf(b, "%d %d %d",
            color_channel_to_255(c.red),
            color_channel_to_255(c.green),
            color_channel_to_255(c.blue));
    return b;
}
