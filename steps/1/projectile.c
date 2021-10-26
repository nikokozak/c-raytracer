#include <stdio.h>
#include "tuple.h"

typedef struct {
    Tuple position; // Point
    Tuple velocity; // Vector
} Projectile;

typedef struct {
    Tuple gravity; // Vector
    Tuple wind; // Vector
} Env;

Projectile tick(Env *env, Projectile *proj)
{
   Tuple position = tuple_add(proj->position, proj->velocity);
   Tuple velocity = tuple_add(tuple_add(proj->velocity, env->gravity), env->wind);
   return (Projectile) { position, velocity };
}

int main(void)
{
    Tuple velocity = tuple_make_vector(1.0, 1.0, 0.0);
    Projectile p = { tuple_make_point(0.0, 1.0, 0.0), tuple_normalize(velocity) };
    Env e = { tuple_make_vector(0.0, -0.1, 0.0), tuple_make_vector(-0.01, 0.0, 0.0) };

    int count = 0;

    puts("Shooting projectile!");
    while (p.position.y >= 0.0)
    {
        count++;
        printf("%d: x[%f], y[%f], z[%f]\n", count, p.position.x, p.position.y, p.position.z);
        p = tick(&e, &p);
    }
    puts("Projectile landed!");
}
