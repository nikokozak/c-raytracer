#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "canvas.h"

Canvas *canvas_make(int width, int height)
{
    int len = width * height;

    Canvas *c = malloc(sizeof(Canvas) + len * sizeof(Color));
    c->width = width;
    c->height = height;

    for (int i = 0; i < width * height; i++)
    {
        c->pixels[i] = (Color) { 0.0, 0.0, 0.0 };
    }

    return c;
}

Canvas *canvas_write_pixel(Canvas *ca, int row, int col, Color co)
{
    int index = canvas_pixel_index_at(ca, row, col);
    ca->pixels[index] = co;
    return ca;
}

int canvas_pixel_index_at(Canvas *c, int row, int col)
{
    return col + (c->width * row);
}

Color canvas_pixel_at(Canvas *c, int row, int col)
{
    return c->pixels[canvas_pixel_index_at(c, row, col)];
}

char *canvas_ppm_header(Canvas *c)
{
    char *header = (char*)malloc(30 * sizeof(char));
    sprintf(header, "P3\n%d %d\n255\n", c->width, c->height);
    return header; 
}

char *_pixel_to_ppm(Color c)
{
    char *ps = (char*)malloc(12 * sizeof(char));

    sprintf(ps, "%d %d %d ",
            color_to_255(c.red),
            color_to_255(c.green),
            color_to_255(c.blue));

    return ps;
}

char *canvas_ppm_body(Canvas *c)
{
    char *ppm_body = (char*)malloc(sizeof(char));
    ppm_body[0] = '\0';

    for (int i = 0; i < c->height * c->width; i++)
    {
        strcat(ppm_body, _pixel_to_ppm(c->pixels[i]));
    }
    return ppm_body;
}

char *canvas_to_ppm(Canvas *c)
{
    char *header = canvas_ppm_header(c);
    const int pixels_len = c->width * c->height;
    const int pixel_ind_size = 12;
    const int header_size = strlen(header);
    
    char *body = canvas_ppm_body(c);
    
    strcat(header, body);
    return header;
}

void canvas_kill(Canvas *c)
{
    free(c);
}
