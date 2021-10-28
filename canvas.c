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

Canvas *canvas_write_pixel(Canvas *ca, int row, int col, Color co)
{
    ca->pixels[utils_rf_index(row, col, ca->width)] = co;
    return ca;
}

Color canvas_pixel_at(Canvas *c, int row, int col)
{
    return c->pixels[utils_rf_index(row, col, c->width)];
}

char *canvas_ppm_header(Canvas *c)
{
    char *header = (char*)malloc(30 * sizeof(char));
    sprintf(header, "P3\n%d %d\n255\n", c->width, c->height);
    return header; 
}

char *canvas_ppm_body(Canvas *c)
{
    const long unsigned ppm_size = MAX_PPM_LINE_LEN * c->height + c->height;
    char *ppm_body = (char*)malloc(ppm_size * sizeof(char));
    ppm_body[0] = '\0';

    for (int row = 0; row < c->height; row++) {

        // 70 char limit counter
        int width_so_far = 0;

        for (int col = 0; col < c->width; col++) {

            const Color pixel = canvas_pixel_at(c, row, col);
            const double colors[] = { pixel.red, pixel.green, pixel.blue };

            for (int i = 0; i < 3; i++) 
            {
                char *channel_s = color_channel_to_s(colors[i]);
                strcat(ppm_body, channel_s);
                
                // Ensure line doesn't exceed 70 chars.
                if (width_so_far + 4 > 70) {
                    strcat(ppm_body, "\n");
                    width_so_far = 0;
                } else {
                    strcat(ppm_body, " ");
                    width_so_far += strlen(channel_s);
                }
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
