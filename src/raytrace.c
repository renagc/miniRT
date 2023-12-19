/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qwerty <qwerty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:01:08 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/19 23:31:27 by qwerty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

//t_rgb	*add_color(t_rgb *color1, t_rgb color2, double i, t_scene *scene)
//{
//	static t_rgb	result;
//	int				x;
//
//	x = color2.r / (255 * i);
//	if (x <= 1 && !scene->l)
//		result.r = color1->r * x;
//	else
//		result.r = color1->r;
//	
//	x = color2.g / (255 * i);
//	if (x <= 1 && !scene->l)
//		result.g = color1->g;
//	else
//		result.g = color1->g * x;
//	x = color2.b / (255 * i);
//	if (x <= 1 && !scene->l)
//		result.b = color1->b;
//	else
//		result.b = color1->b * x;
//	return (&result);
// add_color(rt->closest.color, scene->a->color, scene->a->ratio, scene)
//}


t_rgb	*trace_ray(t_raytrace *rt, t_scene *scene)
{
	t_coord		n;

	rt->closest.t = __DBL_MAX__;
	rt->closest.hit = false;
	rt->closest.color = NULL;
	rt->closest.pos = NULL;
	rt->closest.x = -1;
	closest_intersection(1, __DBL_MAX__, rt, scene);
	if (rt->closest.hit == false)
		return (NULL);
	rt->ray_origin = add_const(&rt->ray_origin, &rt->ray_canvas, rt->closest.t);
	if (rt->closest.type == PL || \
		(rt->closest.type == CY && rt->closest.x == 1))
		n = ((t_plane *)rt->closest.obj)->ori;
	else if (rt->closest.type == SP)
	{
		n = subtract_const(&rt->ray_origin, rt->closest.pos, 1);
		vec_normalize(&n);
	}
	else if (rt->closest.type == CY)
		n = get_cylinder_normal(&rt->ray_origin, rt->closest.obj);
	return (multiply_color(rt->closest.color, compute_light(rt, &n, scene)));
}

void	start_ray_utils(t_raytrace *rt, int *axis, \
		t_viewport vp, t_matrix m)
{
	rt->ray_canvas = canvas_to_viewport(axis[0], axis[1], vp);
	rt->ray_canvas = multiply_by_matrix(rt->ray_canvas, m);
	rt->ray_canvas = subtract_const(&rt->ray_canvas, &rt->ray_origin, 1);
	vec_normalize(&rt->ray_canvas);
}

void	start_ray(t_scene *scene, t_raytrace *rt)
{
	int			axis[2];
	t_viewport	vp;
	t_matrix	m;
	t_coord		vec;

	vec = new_coord(0, 0, 0);
	m = look_at(&scene->c->pos, &scene->c->ori);
	vp = get_viewport_dimensions(scene->c->fov);
	scene->mlx.img = ft_new_image(scene->mlx.ref, C_W, C_H);
	axis[0] = - (C_W / 2) - 1;
	while (++axis[0] < (C_W / 2))
	{
		axis[1] = - (C_H / 2) - 1;
		while (++axis[1] < (C_H / 2))
		{
			rt->ray_origin = multiply_by_matrix(vec, m);
			start_ray_utils(rt, axis, vp, m);
			turn_pixel_to_color(&scene->mlx.img.pixels[(axis[0] + C_W / 2) * 4 \
				+ scene->mlx.img.line_size * \
				(-axis[1] + C_H / 2)], trace_ray(rt, scene));
		}
	}
	mlx_put_image_to_window(scene->mlx.ref, scene->mlx.win, \
		scene->mlx.img.reference, 0, 0);
}

void	closest_intersection(double t_min, double t_max, \
		t_raytrace *rt, t_scene *scene)
{
	t_object	*temp;

	temp = scene->obj;
	while (temp)
	{
		if (temp->type == PL)
			intersect_ray_plane(t_min, t_max, rt, temp->data);
		else if (temp->type == SP)
			intersect_ray_sphere(t_min, t_max, rt, temp->data);
		else if (temp->type == CY)
			intersect_ray_cylinder(t_min, t_max, rt, temp->data);
		temp = temp->next;
	}
}
