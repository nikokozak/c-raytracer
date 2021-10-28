#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "canvas.h"

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

    sprintf(ps, "%d %d %d",
            color_to_255(c.red),
            color_to_255(c.green),
            color_to_255(c.blue));

    return ps;
}

char *canvas_ppm_body(Canvas *c)
{
    char *ppm_body = (char*)malloc((MAX_PPM_LINE_LEN * c->height + c->height) * sizeof(char));
    ppm_body[0] = '\0';

    for (int y = 0; y < c->height; y++) {

        // 70 char limit counter
        int width_so_far = 0;

        for (int x = 0; x < c->width; x++) {

            const char *pixel_ppm = _pixel_to_ppm(canvas_pixel_at(c, x, y));
            const int pixel_str_len = strlen(pixel_ppm);
            width_so_far += pixel_str_len;

            // Ensure line doesn't exceed 70 chars.
            if (width_so_far > 70) {
                strcat(ppm_body, "\n");
                width_so_far = 0;
            }

            // ... + "255 0 0"
            strcat(ppm_body, _pixel_to_ppm(canvas_pixel_at(c, x, y)));

            if (x + 1 != c->width) {
                strcat(ppm_body, " ");
            }
        }
        strcat(ppm_body, "\n");
    }
    return ppm_body;
}

char *canvas_to_ppm(Canvas *c)
{

    const unsigned long result_size = (MAX_PPM_HEADER_LEN + MAX_PPM_LINE_LEN * c->height + c->height) * sizeof(char);
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
