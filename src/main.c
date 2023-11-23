/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:23:41 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/11/23 15:40:01 by rgomes-c         ###   ########.fr       */
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

t_coord		get_cylinder_normal(t_coord *point, t_cylinder *cylinder)
{
	t_coord	ctp;
	t_coord	n;
	t_coord	normal;
	double	pt;

	ctp = subtract_const(point, cylinder->pos, 1);
	pt = product(cylinder->ori, &ctp);
	n.x = cylinder->ori->x * pt;
	n.y = cylinder->ori->y * pt;
	n.z = cylinder->ori->z * pt;
	normal = subtract_const(&ctp, &n, 1);
	vec_normalize(&normal);
	return (normal);
}

// void		check_t(double *t, t_cylinder *cylinder, t_raytrace *rt)
// {
// 	t_coord	q;
// 	t_coord	p2;
// 	t_coord	temp1;
// 	t_coord	temp2;
// 	t_coord	sub1;
// 	t_coord	sub2;

// 	temp1.x = cylinder->ori->x * cylinder->h;
// 	temp1.y = cylinder->ori->y * cylinder->h;
// 	temp1.z = cylinder->ori->z * cylinder->h;
// 	p2 = add_const(cylinder->pos, &temp1, 1);
// 	temp2.x = rt->ray_canvas.x * *t;
// 	temp2.y = rt->ray_canvas.y * *t;
// 	temp2.z = rt->ray_canvas.z * *t;
// 	q = add_const(&rt->ray_origin, &temp2, 1);
// 	sub1 = subtract_const(&q, cylinder->pos, 1);
// 	if (product(cylinder->ori, &sub1) <= 0)
// 		*t = -1;
// 	sub2 = subtract_const(&q, &p2, 1);
// 	if (product(cylinder->ori, &sub2) >= 0)
// 		*t = -1;
// }

// t_coord *multiply(t_coord *point, double x)
// {
// 	t_coord	coord;

// 	coord.x = point->x * x;
// 	coord.y = point->y * x;
// 	coord.z = point->z * x;
// 	return (&coord);
// }

// int			cyl_get_roots(double t_min, double t_max, double *t0, double *t1, t_cylinder *cylinder,
// 								t_raytrace *rt)
// {
// 	t_coord	a_sqrt;
// 	t_coord	right;
// 	double	a;
// 	double	b;
// 	double	c;
// 	t_coord	sub1;

// 	a_sqrt = subtract_const(&rt->ray_canvas, multiply(cylinder->ori, product(&rt->ray_canvas, cylinder->ori)), 1);
// 	a = product(&a_sqrt, &a_sqrt);
// 	sub1 = subtract(&rt->ray_origin, cylinder->pos);
// 	right = subtract(&sub1, multiply(cylinder->ori, product(&sub1, cylinder->ori)));
// 	b = 2 * product(&a_sqrt, &right);
// 	c = product(&right, &right) - ((cylinder->d / 2) * (cylinder->d / 2));
// 	c = b * b - 4 * a * c;
// 	if (c < 0)
// 		return (0);
// 	*t0 = (-b + sqrt(c)) / (2 * a);
// 	*t1 = (-b - sqrt(c)) / (2 * a);
// 	if (t1 > t_min && t1 < t_max && t1 < t[0])
// 		return (get_closest_obj(rt, t[1], CYLINDER, cylinder->color, cylinder->pos, cy));
// 	if (t0 > t_min && t0 < t_max)
// 		return (get_closest_obj(rt, t[0], CYLINDER, cylinder->color, cylinder->pos, cy));
// 	return (0);
// }

// int			intersect_cylinder(t_ray ray, t_cylinder cylinder, double *t)
// {
// 	double t0;
// 	double t1;

// 	if (!cyl_get_roots(0.001, __DBL_MAX__, &t0, &t1, CYLINDER, ray))
// 		return (0);
// 	if (t0 > 0)
// 		check_t(&t0, &cylinder, ray);
// 	if (t1 > 0)
// 		check_t(&t1, &cylinder, ray);
// 	if (t0 < 0 && t1 < 0)
// 		return (0);
// 	if (t1 < t0)
// 	{
// 		if (t1 > 0)
// 			*t = t1;
// 		else
// 			*t = t0;
// 	}
// 	else
// 	{
// 		if (t0 > 0)
// 			*t = t0;
// 		else
// 			*t = t1;
// 	}
// 	return (1);
// }

int	intersect_ray_cylinder(double t_min, double t_max, t_raytrace *rt, t_cylinder *cy)
{
	t_coord op = subtract_const(&rt->ray_origin, cy->pos, 1);
    double a = rt->ray_canvas.x * rt->ray_canvas.x + rt->ray_canvas.y * rt->ray_canvas.y;
    double b = 2 * op.x * rt->ray_canvas.x + 2 * op.y * rt->ray_canvas.y;
    double c = op.x * op.x + op.y * op.y - (cy->d / 2 * cy->d / 2);

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return -1; // No real roots, ray does not intersect cylinder

    double root1 = (-b + sqrt(discriminant)) / (2 * a);
    double root2 = (-b - sqrt(discriminant)) / (2 * a);

    double z1 = op.z + root1 * rt->ray_canvas.z;
    double z2 = op.z + root2 * rt->ray_canvas.z;

    if (z1 > -cy->h/2 && z1 < cy->h/2 && root1 > t_min && root1 < t_max)
	{
		if (get_closest_obj(rt, root1, CYLINDER, cy->color, cy->pos, cy))
			rt->closest.x = 0;
	}
    if (z2 > -cy->h/2 && z2 < cy->h/2 && root2 > t_min && root2 < t_max && root2 < root1)
	{
		if (get_closest_obj(rt, root2, CYLINDER, cy->color, cy->pos, cy))
			rt->closest.x = 0;
	}
    double tCap1 = (cy->h / 2 - op.z) / rt->ray_canvas.z;
    t_coord pCap1 = { op.x + tCap1 * rt->ray_canvas.x, op.y + tCap1 * rt->ray_canvas.y, cy->h / 2 };
    double tCap2 = (-cy->h / 2 - op.z) / rt->ray_canvas.z;
    t_coord pCap2 = { op.x + tCap2 * rt->ray_canvas.x, op.y + tCap2 * rt->ray_canvas.y, -cy->h / 2 };
    if (tCap1 > t_min && tCap1 < t_max && ((pCap1.x * pCap1.x + pCap1.y * pCap1.y) < pow(cy->d / 2, 2)))
	{
		if (get_closest_obj(rt, tCap1, CYLINDER, cy->color, cy->pos, cy))
			rt->closest.x = 1;
	}
    if (tCap2 > t_min && tCap2 < t_max && ((pCap2.x * pCap2.x + pCap2.y * pCap2.y) < pow(cy->d / 2, 2)) && tCap2 < tCap1)
	{
		if (get_closest_obj(rt, tCap2, CYLINDER, cy->color, cy->pos, cy))
			rt->closest.x = 1;
	}
    return (-1);
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
	double		x_x;

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
		x_x = rt->closest.x;
		closest_intersection(0.00000001, __DBL_MAX__, rt, scene);
		rt->closest.color = color;
		rt->closest.x = x_x;
		if (rt->closest.hit == false)
		{
			n_dot_l = product(n, &rt->ray_canvas);
			if (type == PLANE || (type == CYLINDER && rt->closest.x == 1))
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
	rt->closest.x = -1;
	closest_intersection(1, __DBL_MAX__, rt, scene);
	if (rt->closest.hit == false)
		return (NULL);
	rt->ray_origin = add_const(&rt->ray_origin, &rt->ray_canvas, rt->closest.t);
	if (rt->closest.type == PLANE || (rt->closest.type == CYLINDER && rt->closest.x == 1))
		n = *((t_plane *)rt->closest.obj)->ori;
	else if (rt->closest.type == SPHERE)
	{
		n = subtract_const(&rt->ray_origin, rt->closest.pos, 1);
		vec_normalize(&n);
	}
	else if (rt->closest.type == CYLINDER)
		n = get_cylinder_normal(&rt->ray_origin, rt->closest.obj);
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
