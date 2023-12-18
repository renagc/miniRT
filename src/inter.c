/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:16:35 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/18 21:48:48 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	get_closest_obj_utils(int type, void *obj, t_raytrace *rt)
{
	t_sphere	*sp;
	t_cylinder	*cy;
	t_plane		*pl;

	if (type == SP)
	{
		sp = (t_sphere *)obj;
		rt->closest.color = &sp->color;
		rt->closest.pos = &sp->pos;
	}
	else if (type == CY)
	{
		cy = (t_cylinder *)obj;
		rt->closest.color = &cy->color;
		rt->closest.pos = &cy->pos;
	}
	else if (type == PL)
	{
		pl = (t_plane *)obj;
		rt->closest.color = &pl->color;
		rt->closest.pos = &pl->pos;
	}
}

bool	get_closest_obj(t_raytrace *rt, double t, int type, void *obj)
{
	if (t < rt->closest.t)
	{
		rt->closest.t = t;
		rt->closest.type = type;
		rt->closest.hit = true;
		rt->closest.obj = obj;
		get_closest_obj_utils(type, obj, rt);
		return (true);
	}
	return (false);
}

bool	intersect_ray_sphere(double t_min, double t_max, \
	t_raytrace *rt, t_sphere *sp)
{
	t_coord		co;
	double		a;
	double		b;
	double		c;
	double		t[2];

	co = subtract_const(&rt->ray_origin, &sp->pos, 1);
	a = product(&rt->ray_canvas, &rt->ray_canvas);
	b = 2 * product(&co, &rt->ray_canvas);
	c = product(&co, &co) - ((sp->d / 2) * (sp->d / 2));
	c = b * b - 4 * a * c;
	if (c < 0)
		return (false);
	t[0] = (-b + sqrt(c)) / (2 * a);
	t[1] = (-b - sqrt(c)) / (2 * a);
	if (t[1] > t_min && t[1] < t_max && t[1] < t[0])
		return (get_closest_obj(rt, t[1], SP, sp));
	if (t[0] > t_min && t[0] < t_max)
		return (get_closest_obj(rt, t[0], SP, sp));
	return (false);
}

bool	intersect_ray_plane(double t_min, double t_max, \
	t_raytrace *rt, t_plane *plane)
{
	t_coord	op;
	double	vd;
	double	x;
	double	t;

	vd = product(&plane->ori, &rt->ray_canvas);
	if (fabs(vd) > 0.000001)
	{
		op = subtract_const(&plane->pos, &rt->ray_origin, 1);
		x = product(&op, &plane->ori);
		t = x / vd;
		if (t > t_min && t < t_max)
			return (get_closest_obj(rt, t, PL, plane));
	}
	return (false);
}

int	intersect_ray_cylinder(double t_min, double t_max, \
	t_raytrace *rt, t_cylinder *cy)
{
	t_matrix	transform_matrix;
	t_coord		local_ray[2];
	double		t[4];

	t[2] = t_min;
	t[3] = t_max;
	transform_matrix = matrix_cy(cy);
	local_ray[0] = transform_point(subtract_const(&rt->ray_origin, \
		&cy->pos, 1), transform_matrix.m);
	local_ray[1] = transform_direction(rt->ray_canvas, transform_matrix.m);
	if (!cy_quadratic_f(&local_ray[1], &local_ray[0], cy, t))
		return (-1);
	calc_z(rt, cy, t, local_ray);
	calc_t(rt, cy, local_ray, t);
	return (-1);
}
