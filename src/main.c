/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:23:41 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/30 17:54:09 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <string.h>

typedef struct s_viewport	t_viewport;
typedef struct s_rt			t_rt;

struct s_viewport
{
	double				vw;
	double				vh;
	double				d;
};

struct s_rt
{
	t_viewport	vp;
	t_rgb		bg_color;
	t_coord		*camera_origin;
	t_vector	o_vp;
	t_coord		d;
};

// Assumindo que distancia da camara ao plano de projecao é 1 unidade;
// tan(alpha) = cateto oposto sobre o cateto adjacente;
// para calcular a largura é nada mais do que uma regra de 3 simples;
t_viewport	get_viewport_dimensions(int fov)
{
	t_viewport	viewport;
	double		alpha;
	double		rad;

	rad = fov * (M_PI / 180);
	alpha = rad / 2;
	viewport.d = 1.0;
	viewport.vh = 2 * tan(alpha) * viewport.d;
	viewport.vw = viewport.vh * C_W / C_H;
	return (viewport);
}

// Para calcular cada coordenada do viewport fazemos tambem uma regra 3 simples;
t_coord	canvas_to_viewport(double cx, double cy, t_viewport view)
{
	t_coord	vp;

	(void)view;
	vp.x = cx * view.vw / C_W;
	vp.y = cy * view.vh / C_H;
	vp.z = view.d;
	return (vp);
}

int	intersect_ray_sphere(t_coord *o, t_coord *d, t_sphere *sp, double *t)
{
	t_coord		co;
	double		a;
	double		b;
	double		c;
	double		disc;

	co = subtract_const(o, sp->pos, 1);
	a = product(d, d);
	b = 2 * product(&co, d);
	c = product(&co, &co) - ((sp->d / 2) * (sp->d / 2));
	disc = b * b - 4 * a * c;
	if (d < 0)
		return (0);
	t[0] = (-b + sqrt(disc)) / (2 * a);
	t[1] = (-b - sqrt(disc)) / (2 * a);
	return (1);
}

void	closest_intersection(double t_min, t_coord *o, t_coord *d, t_sphere *sp, double *closest_t, t_sphere **closest_sp)
{
	t_sphere	*temp;
	double		t[2];

	temp = sp;
	while (temp)
	{
		if (intersect_ray_sphere(o, d, temp, t))
		{
			if (t[0] < *closest_t && t[0] > t_min)
			{
				*closest_t = t[0];
				*closest_sp = temp;
			}
			if (t[1] < *closest_t && t[1] > t_min)
			{
				*closest_t = t[1];
				*closest_sp = temp;
			}
		}
		temp = temp->next;
	}
}

double	compute_light(t_coord *p, t_coord *n, t_scene *scene)
{
	double		i;
	t_coord		l;
	double		n_dot_l;
	t_sphere	*shadow_sp;
	double		shadow_t;

	i = 0.0;
	shadow_sp = NULL;
	shadow_t = 1;
	if (scene->a)
		i += scene->a->ratio;
	if (scene->l)
	{
		l = subtract_const(scene->l->pos, p, 1);
		closest_intersection(0.001, p, &l, scene->sp, &shadow_t, &shadow_sp);
		if (shadow_sp == NULL)
		{
			n_dot_l = product(n, &l);
			if (n_dot_l > 0)
				i += scene->l->ratio * (n_dot_l / (vec_length(n) * vec_length(&l)));
		}
	}
	if (i > 1)
		return (1);
	return (i);
}

t_rgb	*trace_ray(t_coord *o, t_coord *d, t_scene *scene)
{
	double		closest_t;
	t_rgb		*color;
	t_sphere	*closest_sphere;
	t_coord		p;
	t_coord		n;

	closest_t = __DBL_MAX__;
	closest_sphere = NULL;
	closest_intersection(1, o, d, scene->sp, &closest_t, &closest_sphere);
	if (closest_sphere == NULL)
		return (NULL);
	p = add_const(o, d, closest_t);
	n = subtract_const(&p, closest_sphere->pos, 1);
	vec_normalize(&n);
	color = multiply_color(closest_sphere->color, compute_light(&p, &n, scene));
	return (color);
}

void	start_ray(t_scene *scene, void *mlx, void *mlx_window)
{
	int			x;
	int			y;
	t_image		img;
	t_viewport	vp;
	t_coord		d;
	t_rgb		*color;

	vp = get_viewport_dimensions(scene->c->fov);
	img = ft_new_image(mlx, C_W, C_H);
	x = - (C_W / 2) - 1;
	while (++x < (C_W / 2))
	{
		y = - (C_H / 2) - 1;
		while (++y < (C_H / 2))
		{
			d = canvas_to_viewport(x, y, vp);
			color = trace_ray(scene->c->pos, &d, scene);
			turn_pixel_to_color(&img.pixels[(x + C_W / 2) * 4 + img.line_size * (-y + C_H / 2)], color);
		}
	}
	mlx_put_image_to_window(mlx, mlx_window, img.reference, 0, 0);
}

int	main(int ac, char **av)
{
	t_scene	*scene;
	void	*mlx;
	void	*mlx_win;

	scene = NULL;
	parse(ac, av, &scene);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, C_W, C_H, "Test");
	//debug(scene);
	start_ray(scene, mlx, mlx_win);
	mlx_loop(mlx);
	return (0);
}
