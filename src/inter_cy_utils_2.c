/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cy_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:50:25 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/18 21:49:56 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// Calculate the z-coordinates at the intersection points
void	calc_z(t_raytrace *rt, t_cylinder *cy, double *t, t_coord *local_ray)
{
	double	z[2];

	z[0] = local_ray[0].z + t[0] * local_ray[1].z;
	z[1] = local_ray[0].z + t[1] * local_ray[1].z;
	if (z[0] > -cy->h / 2 && z[0] < cy->h / 2 && t[0] > t[2] \
		&& t[0] < t[3] && \
		get_closest_obj(rt, t[0], CY, cy))
		rt->closest.x = 0;
	if (z[1] > -cy->h / 2 && z[1] < cy->h / 2 && t[1] > t[2] \
		&& t[1] < t[3] && t[1] < t[0] && \
		get_closest_obj(rt, t[1], CY, cy))
		rt->closest.x = 0;
}

void	calc_t(t_raytrace *rt, t_cylinder *cy, \
	t_coord *local_ray, double *t)
{
	double	t_cap1;
	double	t_cap2;
	t_coord	p_cap1;
	t_coord	p_cap2;

	t_cap1 = (-cy->h / 2 - local_ray[0].z) / local_ray[1].z;
	t_cap2 = (cy->h / 2 - local_ray[0].z) / local_ray[1].z;
	p_cap1 = new_coord(local_ray[0].x + t_cap1 * local_ray[1].x, \
		local_ray[0].y + t_cap1 * local_ray[1].y, -cy->h / 2);
	p_cap2 = new_coord(local_ray[0].x + t_cap2 * local_ray[1].x, \
		local_ray[0].y + t_cap2 * local_ray[1].y, cy->h / 2);
	if (t_cap1 > t[2] && t_cap1 < t[3] && \
		(p_cap1.x * p_cap1.x + p_cap1.y * p_cap1.y) < (cy->d / 2 * cy->d / 2))
	{
		if (get_closest_obj(rt, t_cap1, CY, cy))
			rt->closest.x = 1;
	}
	if (t_cap2 > t[2] && t_cap2 < t[3] && \
		(p_cap2.x * p_cap2.x + p_cap2.y * p_cap2.y) < (cy->d / 2 * cy->d / 2))
	{
		if (get_closest_obj(rt, t_cap2, CY, cy))
			rt->closest.x = 1;
	}
}
