#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "canvas.h"
#include "utils.h"

// Max possible length of the P3... header
#define MAX_PPM_HEADER_LEN 21
#define MAX_PPM_LINE_LEN 70

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

Canvas *canvas_write_pixel(Canvas *ca, int x, int y, Color co)
{
    const int index = utils_rf_index(x, y, ca->width);

    if (index < 0 || index >= ca->width * ca->height) { return ca; }

    ca->pixels[index] = co;
    return ca;
}

Color canvas_pixel_at(Canvas *c, int x, int y)
{
    return c->pixels[utils_rf_index(x, y, c->width)];
}

char *canvas_ppm_header(Canvas *c)
{
    char *header = (char*)malloc(30 * sizeof(char));
    sprintf(header, "P3\n%d %d\n255\n", c->width, c->height);
    return header; 
}

char *canvas_ppm_body(Canvas *c)
{
    const long unsigned ppm_size = c->height * c->width * 10;
    char *ppm_body = (char*)malloc(ppm_size * sizeof(char));
    ppm_body[0] = '\0';

    for (int row = 0; row < c->height; row++)
    {
        strcat(ppm_body, canvas_ppm_row(c, row));
    }

    return ppm_body;
}

void shorten_ppm_row(char *row, int max_length)
{
    if (strlen(row) < 70) { return; }
    int replacement_index = max_length;

    while (replacement_index < strlen(row)) {
        char at_index = row[replacement_index];

        while (at_index != ' ') {
            at_index = row[--replacement_index];
        }

        row[replacement_index++] = '\n';
        replacement_index += max_length;
    }
}

char *canvas_ppm_row(Canvas *c, int row)
{
    char *ppm_row = (char*)malloc(c->width * 12 * sizeof(char));
    int length_so_far = 0;
    int max_length = 70;

    for (int x = 0; x < c->width; x++)
    {
        Color pixel = canvas_pixel_at(c, x, row);

        strcat(ppm_row, color_channel_to_s(pixel.red));
        strcat(ppm_row, " ");
        strcat(ppm_row, color_channel_to_s(pixel.green));
        strcat(ppm_row, " ");
        strcat(ppm_row, color_channel_to_s(pixel.blue));

        if (x + 1 == c->width) {
            strcat(ppm_row, "\n");
        } else {
            strcat(ppm_row, " ");
        }
    }

    shorten_ppm_row(ppm_row, max_length);
    return ppm_row;
}

char *canvas_to_ppm(Canvas *c)
{

    const unsigned long result_size = (MAX_PPM_HEADER_LEN + (c->width * c->height * 12)) * sizeof(char);
    char *result = (char*)malloc(result_size);
    result[0] = '\0';

    char *header = canvas_ppm_header(c);
    char *body = canvas_ppm_body(c);

    strcat(result, header);
    strcat(result, body);
    return result;
}

void canvas_kill(Canvas *c)
{
    free(c);
}
