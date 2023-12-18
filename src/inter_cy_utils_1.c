/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cy_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:49:34 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/18 20:57:08 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// Calculate coefficients for the quadratic equation
bool	cy_quadratic_f(t_coord *local_ray_dir, \
	t_coord *local_ray_ori, t_cylinder *cy, double *t)
{
	double	a;
	double	b;
	double	c;
	double	disc;

	a = local_ray_dir->x * local_ray_dir->x + \
		local_ray_dir->y * local_ray_dir->y;
	b = 2 * (local_ray_ori->x * local_ray_dir->x + \
		local_ray_ori->y * local_ray_dir->y);
	c = local_ray_ori->x * local_ray_ori->x + \
		local_ray_ori->y * local_ray_ori->y - (cy->d / 2 * cy->d / 2);
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (false);
	t[0] = (-b + sqrt(disc)) / (2 * a);
	t[1] = (-b - sqrt(disc)) / (2 * a);
	return (true);
}

// Check if the intersection points on the caps are within the cylinder's radius
t_coord	*check_cap(double *t, t_coord *local_ray_origin, \
	t_coord *local_ray_dir, t_cylinder *cy)
{
	static t_coord	p_cap[2];

	t[0] = (-cy->h / 2 - local_ray_origin->z) / local_ray_dir->z;
	t[1] = (cy->h / 2 - local_ray_origin->z) / local_ray_dir->z;
	p_cap[0] = new_coord(local_ray_origin->x + t[0] * local_ray_dir->x, \
		local_ray_origin->y + t[0] * local_ray_dir->y, -cy->h / 2);
	p_cap[1] = new_coord(local_ray_origin->x + t[1] * local_ray_dir->x, \
		local_ray_origin->y + t[1] * local_ray_dir->y, cy->h / 2);
	return (p_cap);
}

t_matrix	new_matrix(t_coord v1, t_coord v2, t_coord v3)
{
	t_matrix	m;

	m.m[0][0] = v1.x;
	m.m[0][1] = v1.y;
	m.m[0][2] = v1.z;
	m.m[0][3] = 0;
	m.m[1][0] = v2.x;
	m.m[1][1] = v2.y;
	m.m[1][2] = v2.z;
	m.m[1][3] = 0;
	m.m[2][0] = v3.x;
	m.m[2][1] = v3.y;
	m.m[2][2] = v3.z;
	m.m[2][3] = 0;
	m.m[3][0] = 0;
	m.m[3][1] = 0;
	m.m[3][2] = 0;
	m.m[3][3] = 1;
	return (m);
}

// Create the transformation matrix
t_matrix	matrix_cy(t_cylinder *cy)
{
	t_coord	cy_ori;
	t_coord	up;
	t_coord	right;
	t_coord	new_up;

	cy_ori = new_coord((&cy->ori)->x / vec_length(&cy->ori), \
		(&cy->ori)->y / vec_length(&cy->ori), \
			(&cy->ori)->z / vec_length(&cy->ori));
	up = new_coord(0, 0, 1);
	if (fabs(cy_ori.x) == 0 && fabs(cy_ori.y) == 0)
		up.x = 1;
	right = cross_product(&up, &cy_ori);
	new_up = cross_product(&cy_ori, &right);
	return (new_matrix(right, new_up, cy_ori));
}
