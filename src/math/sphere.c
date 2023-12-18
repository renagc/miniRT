/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:52:53 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/17 11:40:37 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

//return NULL if not possible to solve
static double	*solve_quadratic_function(double a, double b, double c)
{
	double	*t;
	double	discriminant;

	discriminant = (b * b) - 4 * a * c;
	if (discriminant < 0)
		return (NULL);
	t = malloc(sizeof(double) * 2);
	if (!t)
		return (NULL);
	t[0] = (-b + sqrt(discriminant)) / (2 * a);
	t[1] = (-b - sqrt(discriminant)) / (2 * a);
	return (t);
}

// atˆ2 + 2bt + c = 0;
double	*ray_intersect_sphere(t_scene *scene, t_sphere *sphere, t_vector *d)
{
	double		a;
	double		b;
	double		c;
	double		r;
	t_vector	co;

	r = sphere->d / 2;
	co = subtract(&scene->c->pos, &sphere->pos);
	a = product((t_coord *)d, (t_coord *)d);
	b = 2 * product((t_coord *)&co, (t_coord *)d);
	c = product((t_coord *)&co, (t_coord *)&co) - r * r;
	return (solve_quadratic_function(a, b, c));
}
