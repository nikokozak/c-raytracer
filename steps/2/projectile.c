#include <stdio.h>
#include "tuple.h"
#include "color.h"
#include "canvas.h"

typedef struct {
    Tuple position; // Point
    Tuple velocity; // Vector
} Projectile;

typedef struct {
    Tuple gravity; // Vector
    Tuple wind; // Vector
} Env;

Canvas *c;

Projectile tick(Env *env, Projectile *proj)
{
   Tuple position = tuple_add(proj->position, proj->velocity);
   Tuple velocity = tuple_add(tuple_add(proj->velocity, env->gravity), env->wind);
   return (Projectile) { position, velocity };
}

int main(void)
{
    FILE *fp = fopen("pic.ppm", "w");
    c = canvas_make(200, 200);

    Tuple velocity = 
        tuple_normalize(tuple_make_vector(0.35, 1.0, 0.0));
    Projectile p = { tuple_make_point(0.0, 1.0, 0.0), tuple_mult(velocity, 6.0) };
    Env e = { tuple_make_vector(0.0, -0.1, 0.0), tuple_make_vector(-0.01, 0.0, 0.0) };

    int count = 0;

    while (p.position.y >= 0.0)
    {
       printf("%d: x[%f], y[%f], z[%f]\n", count, p.position.x, p.position.y, p.position.z);
        int x = (int) p.position.x;
        int y = (int) p.position.y;

        canvas_write_pixel(c, x, c->height - y, color_make(1.0, 0.0, 0.0));
        p = tick(&e, &p);
    }

    canvas_to_ppm(c);
    fputs(canvas_to_ppm(c), fp);

    canvas_kill(c);

    fclose(fp);

}
