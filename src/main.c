/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:23:41 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/11/10 20:18:36 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <string.h>

typedef struct s_viewport	t_viewport;

struct s_viewport
{
	double				vw;
	double				vh;
	double				d;
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

void	get_closest_obj(t_raytrace *rt, double t, void *obj)
{
	if (rt->closest.obj == SPHERE)
	{
		rt->closest.color = ((t_sphere *)obj)->color;
		rt->closest.pos = ((t_sphere *)obj)->pos;
		rt->closest.t = t;
	}
	else if (rt->closest.obj == PLANE)
	{
		rt->closest.color = ((t_plane *)obj)->color;
		rt->closest.pos = ((t_plane *)obj)->pos;
		rt->closest.t = t;
	}
	else if (rt->closest.obj == CYLINDER)
	{
		rt->closest.color = ((t_cylinder *)obj)->color;
		rt->closest.pos = ((t_cylinder *)obj)->pos;
		rt->closest.t = t;
	}
}

void	intersect_ray_sphere(double t_min, double t_max, t_raytrace *rt, t_sphere *sp)
{
	t_coord		co;
	double		a;
	double		b;
	double		c;
	double		disc;
	double		t[2];

	co = subtract_const(&rt->o, sp->pos, 1);
	a = product(&rt->d, &rt->d);
	b = 2 * product(&co, &rt->d);
	c = product(&co, &co) - ((sp->d / 2) * (sp->d / 2));
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return ;
	t[0] = (-b + sqrt(disc)) / (2 * a);
	t[1] = (-b - sqrt(disc)) / (2 * a);
	if (t[0] < rt->closest.t && t[0] > t_min && t[0] < t_max)
	{
		rt->closest.obj = SPHERE;
		get_closest_obj(rt, t[0], sp);
	}
	if (t[1] < rt->closest.t && t[1] > t_min && t[1] < t_max)
	{
		rt->closest.obj = SPHERE;
		get_closest_obj(rt, t[1], sp);
	}
}

void	intersect_ray_plane(double t_min, double t_max, t_raytrace *rt, t_plane *plane)
{
	t_coord	op;
	double	vd;
	double	t;

	op = subtract_const(&rt->o, plane->pos, 1);
	vd = -product(plane->ori, &op);
	if (vd == 0)
		return ;
	t = vd / product(&rt->d, plane->ori);
	if (t < rt->closest.t && t > t_min && t < t_max)
	{
		rt->closest.obj = PLANE;
		get_closest_obj(rt, t, plane);
	}
}
void	intersect_ray_cylinder(double t_min, double t_max, t_raytrace *rt, t_cylinder *cylinder)
{
	t_coord		op;
	double		a;
	double		b;
	double		c;
	double		disc;
	double		ori;
	double		t[2];

	op = subtract_const(&rt->o, cylinder->pos, 1);
	ori = vec_length(cylinder->ori) * vec_length(cylinder->ori);
	a = product(&rt->d, &rt->d) * ori - product(&rt->d, cylinder->ori) * product(&rt->d, cylinder->ori);
	b = 2 * product(&op, &rt->d) * ori - product(&rt->d, cylinder->ori) * product(&rt->d, cylinder->ori);
	c = product(&op, &op) - ((cylinder->d / 2) * (cylinder->d / 2)) - product(&rt->d, cylinder->ori) * product(&rt->d, cylinder->ori);
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return ;
	t[0] = (-b + sqrt(disc)) / (2 * a);
	t[1] = (-b - sqrt(disc)) / (2 * a);
	if (t[0] < rt->closest.t && t[0] > t_min && t[0] < t_max)
	{
		rt->closest.obj = CYLINDER;
		get_closest_obj(rt, t[0], cylinder);
	}
	if (t[1] < rt->closest.t && t[1] > t_min && t[1] < t_max)
	{
		rt->closest.obj = CYLINDER;
		get_closest_obj(rt, t[1], cylinder);
	}
}

int	closest_intersection(double t_min, double t_max, t_raytrace *rt, t_scene *scene)
{
	t_sphere	*temp_sp;
	t_plane		*temp_pl;
	// t_cylinder	*temp_cy;

	temp_sp = scene->sp;
	while (temp_sp)
	{
		intersect_ray_sphere(t_min, t_max, rt, temp_sp);
		temp_sp = temp_sp->next;
	}
	temp_pl = scene->pl;
	while (temp_pl)
	{
		intersect_ray_plane(t_min, t_max, rt, temp_pl);
		temp_pl = temp_pl->next;
	}
	// temp_cy = scene->cy;
	// while (temp_cy)
	// {
	// 	intersect_ray_cylinder(t_min, t_max, rt, (void *)temp_cy);
	// 	temp_cy = temp_cy->next;
	// }
	return (1);
}

double	compute_light(t_raytrace *rt, t_coord *n, t_scene *scene)
{
	double		i;
	double		n_dot_l;

	i = 0.0;
	rt->closest.obj = 0;
	rt->closest.color = NULL;
	rt->closest.pos = NULL;
	if (scene->a)
		i += scene->a->ratio;
	if (scene->l)
	{
		rt->d = subtract_const(scene->l->pos, &rt->o, 1);
		closest_intersection(0.001, 1, rt, scene);
		if (rt->closest.obj == 0)
		{
			n_dot_l = product(n, &rt->d);
			if (n_dot_l > 0)
				i += scene->l->ratio * n_dot_l / (vec_length(n) * vec_length(&rt->d));
		}
	}
	if (i > 1)
		return (1);
	return (i);
}

t_rgb	*trace_ray(t_raytrace *rt, t_scene *scene)
{
	t_coord		n;

	rt->o = *scene->c->pos;
	rt->closest.obj = 0;
	rt->closest.color = NULL;
	rt->closest.pos = NULL;
	rt->closest.t = __DBL_MAX__;
	closest_intersection(1, __DBL_MAX__, rt, scene);
	if (rt->closest.obj == 0)
		return (NULL);
	rt->o = add_const(&rt->o, &rt->d, rt->closest.t);
	n = subtract_const(&rt->o, rt->closest.pos, 1);
	vec_normalize(&n);
	// if (compute_light(rt, &n, scene) == scene->a->ratio)
	// 	return (rt->closest.color);
	// else
	return (multiply_color(rt->closest.color, compute_light(rt, &n, scene)));
}

void	start_ray(t_scene *scene, void *mlx, void *mlx_window)
{
	int			x;
	int			y;
	t_image		img;
	t_viewport	vp;
	t_raytrace	rt;
	t_rgb		*color;

	vp = get_viewport_dimensions(scene->c->fov);
	img = ft_new_image(mlx, C_W, C_H);
	x = - (C_W / 2) - 1;
	while (++x < (C_W / 2))
	{
		y = - (C_H / 2) - 1;
		while (++y < (C_H / 2))
		{
			rt.d = canvas_to_viewport(x, y, vp);
			color = trace_ray(&rt, scene);
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
