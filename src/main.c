/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:23:41 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/11/20 12:23:35 by rgomes-c         ###   ########.fr       */
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

bool	get_closest_obj(t_raytrace *rt, double t, int type, t_rgb *color, t_coord *pos, void *obj)
{
	if (t < rt->closest.t)
	{
		rt->closest.t = t;
		rt->closest.color = color;
		rt->closest.pos = pos;
		rt->closest.type = type;
		rt->closest.hit = true;
		rt->closest.obj = obj;
		return (true);
	}
	return (false);
}

bool	intersect_ray_sphere(double t_min, double t_max, t_raytrace *rt, t_sphere *sp)
{
	t_coord		co;
	double		a;
	double		b;
	double		c;
	double		t[2];

	co = subtract_const(&rt->ray_origin, sp->pos, 1);
	a = product(&rt->ray_canvas, &rt->ray_canvas);
	b = 2 * product(&co, &rt->ray_canvas);
	c = product(&co, &co) - ((sp->d / 2) * (sp->d / 2));
	c = b * b - 4 * a * c;
	if (c < 0)
		return (false);
	t[0] = (-b + sqrt(c)) / (2 * a);
	t[1] = (-b - sqrt(c)) / (2 * a);
	if (t[1] > t_min && t[1] < t_max && t[1] < t[0])
		return (get_closest_obj(rt, t[1], SPHERE, sp->color, sp->pos, sp));
	if (t[0] > t_min && t[0] < t_max)
		return (get_closest_obj(rt, t[0], SPHERE, sp->color, sp->pos, sp));
	return (false);
}

bool	intersect_ray_plane(double t_min, double t_max, t_raytrace *rt, t_plane *plane)
{
	t_coord	op;
	double	vd;
	double	x;
	double	t;

	vd = product(plane->ori, &rt->ray_canvas);
	if (fabs(vd) > 0.000001)
	{
		op = subtract_const(plane->pos, &rt->ray_origin, 1);
		x = product(&op, plane->ori);
		t = x / vd;
		if (t > t_min && t < t_max)
			return (get_closest_obj(rt, t, PLANE, plane->color, plane->pos, plane));
	}
	return (false);
}

void	intersect_ray_cylinder(double t_min, double t_max, t_raytrace *rt, t_cylinder *cy)
{
	t_coord	op;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t[2];

	op = subtract_const(&rt->ray_origin, cy->ori, 1);
	a = product(&rt->ray_canvas, &rt->ray_canvas) * pow(vec_length(cy->ori), 2) - pow(product(&rt->ray_canvas, cy->ori), 2);
	b = 2 * product(&op, &rt->ray_canvas) * pow(vec_length(cy->ori), 2) - 2 * product(&rt->ray_canvas, cy->ori) * product(&op, cy->ori);
	c = product(&op, &op) * pow(vec_length(cy->ori), 2) - pow(product(&op, cy->ori), 2) - pow(cy->d / 2, 2) * pow(vec_length(cy->ori), 2);
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return ;
	t[0] = (-b + sqrt(disc)) / (2 * a);
	t[1] = (-b - sqrt(disc)) / (2 * a);
	if (t[0] > t_min && t[0] < t_max)
		get_closest_obj(rt, t[0], CYLINDER, cy->color, cy->pos, cy);
	if (t[1] > t_min && t[1] < t_max && t[1] < t[0])
		get_closest_obj(rt, t[1], CYLINDER, cy->color, cy->pos, cy);
}
// void	intersect_ray_cylinder(double t_min, double t_max, t_raytrace *rt, t_cylinder *cylinder)
// {
// 	t_coord		op;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		disc;
// 	double		ori;
// 	double		t[2];

// 	op = subtract_const(&rt->ray_origin, cylinder->pos, 1);
// 	ori = vec_length(cylinder->ori) * vec_length(cylinder->ori);
// 	a = product(&rt->ray_canvas, &rt->ray_canvas) * ori - product(&rt->ray_canvas, cylinder->ori) * product(&rt->ray_canvas, cylinder->ori);
// 	b = 2 * product(&op, &rt->ray_canvas) * ori - product(&rt->ray_canvas, cylinder->ori) * product(&rt->ray_canvas, cylinder->ori);
// 	c = product(&op, &op) - ((cylinder->d / 2) * (cylinder->d / 2)) - product(&rt->ray_canvas, cylinder->ori) * product(&rt->ray_canvas, cylinder->ori);
// 	disc = b * b - 4 * a * c;
// 	if (disc < 0)
// 		return ;
// 	t[0] = (-b + sqrt(disc)) / (2 * a);
// 	t[1] = (-b - sqrt(disc)) / (2 * a);
// 	if (t[0] > t_min && t[0] < t_max)
// 		get_closest_obj(rt, t[0], CYLINDER, cylinder->color, cylinder->pos, cylinder);
// 	if (t[1] > t_min && t[1] < t_max && t[1] < t[0])
// 		get_closest_obj(rt, t[1], CYLINDER, cylinder->color, cylinder->pos, cylinder);
// }

void	closest_intersection(double t_min, double t_max, t_raytrace *rt, t_scene *scene)
{
	t_object	*temp;

	temp = scene->obj;
	while (temp)
	{
		if (temp->type == PLANE)
			intersect_ray_plane(t_min, t_max, rt, temp->data);
		else if (temp->type == SPHERE)
			intersect_ray_sphere(t_min, t_max, rt, temp->data);
		else if (temp->type == CYLINDER)
			intersect_ray_cylinder(t_min, t_max, rt, temp->data);
		temp = temp->next;
	}
}

double	compute_light(t_raytrace *rt, t_coord *n, t_scene *scene)
{
	double		i;
	double		n_dot_l;
	t_rgb		*color;
	double		type;

	i = 0.0;
	color = rt->closest.color;
	type = rt->closest.type;
	rt->closest.t = 1;
	if (scene->a)
		i += scene->a->ratio;
	if (scene->l)
	{
		rt->ray_canvas = subtract_const(scene->l->pos, &rt->ray_origin, 1);
		rt->closest.hit = false;
		closest_intersection(0.001, __DBL_MAX__, rt, scene);
		rt->closest.color = color;
		if (rt->closest.hit == false)
		{
			n_dot_l = product(n, &rt->ray_canvas);
			if (type == PLANE)
				i += scene->l->ratio * fabs(n_dot_l) / (vec_length(n) * vec_length(&rt->ray_canvas));
			else if (n_dot_l > 0)
				i += scene->l->ratio * n_dot_l / (vec_length(n) * vec_length(&rt->ray_canvas));
		}
	}
	if (i > 1)
		return (1);
	return (i);
}

t_rgb	*trace_ray(t_raytrace *rt, t_scene *scene)
{
	t_coord		n;

	rt->ray_origin = *scene->c->pos;
	rt->closest.t = __DBL_MAX__;
	rt->closest.hit = false;
	rt->closest.color = NULL;
	rt->closest.pos = NULL;
	closest_intersection(1, __DBL_MAX__, rt, scene);
	if (rt->closest.hit == false)
		return (NULL);
	rt->ray_origin = add_const(&rt->ray_origin, &rt->ray_canvas, rt->closest.t);
	if (rt->closest.type == PLANE)
		n = *((t_plane *)rt->closest.obj)->ori;
	else
	{
		n = subtract_const(&rt->ray_origin, rt->closest.pos, 1);
		vec_normalize(&n);
	}
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
			rt.ray_canvas = canvas_to_viewport(x, y, vp);
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
	debug(scene);
	start_ray(scene, mlx, mlx_win);
	mlx_loop(mlx);
	return (0);
}
