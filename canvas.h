#ifndef RAYTRACE_CANVAS
#define RAYTRACE_CANVAS
#include "color.h"

typedef struct Canvas {
    int width;
    int height;
    Color pixels[];
} Canvas;

Canvas *canvas_make(int, int);
void canvas_kill(Canvas*);

Canvas *canvas_write_pixel(Canvas*, int, int, Color);
int canvas_pixel_index_at(Canvas*, int, int);
Color canvas_pixel_at(Canvas*, int, int);
char *canvas_ppm_header(Canvas*);
char *canvas_ppm_body(Canvas*);
char *canvas_ppm_row(Canvas*, int);
char *canvas_to_ppm(Canvas*);
#endif
