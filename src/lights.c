/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:38:58 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/18 21:39:04 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

double	diffuse(int type, t_coord *n, t_raytrace *rt, t_scene *scene)
{
	double	n_dot_l;
	double	i;

	i = 0.0;
	n_dot_l = product(n, &rt->ray_canvas);
	if (type == PL || (type == CY && rt->closest.x == 1))
		i += scene->l->ratio * fabs(n_dot_l) / \
			(vec_length(n) * vec_length(&rt->ray_canvas));
	else if (n_dot_l > 0)
		i += scene->l->ratio * n_dot_l / \
			(vec_length(n) * vec_length(&rt->ray_canvas));
	return (i);
}

double	compute_light(t_raytrace *rt, t_coord *n, t_scene *scene)
{
	double		i;
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
		rt->ray_canvas = subtract_const(&scene->l->pos, &rt->ray_origin, 1);
		rt->closest.hit = false;
		x_x = rt->closest.x;
		closest_intersection(0.00000001, __DBL_MAX__, rt, scene);
		rt->closest.color = color;
		rt->closest.x = x_x;
		if (rt->closest.hit == false)
			i += diffuse(type, n, rt, scene);
	}
	if (i > 1)
		return (1);
	return (i);
}