#include <minirt.h>

double  compute_lighting(t_scene *scene, t_vector *p, t_vector *n)
{
    double      intensity;
    t_vector    l;
    double      n_dot_l;

    intensity = 0;
    if (scene->a)
        intensity += scene->a->ratio;
    if (scene->l)
    {
        l = subtract(scene->l->pos, (t_coord *)p);
        n_dot_l = product(n, &l);
        if (n_dot_l > 0)
            intensity += scene->l->ratio * (n_dot_l / (vec_length(n) * vec_length(&l)));
    }
    return (intensity);

}
