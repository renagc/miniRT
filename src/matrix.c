/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:12:42 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/18 16:41:11 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_coord	cross_product(t_coord *a, t_coord *b)
{
	t_coord	result;

	result.x = a->y * b->z - a->z * b->y;
	result.y = a->z * b->x - a->x * b->z;
	result.z = a->x * b->y - a->y * b->x;
	return (result);
}

t_coord	multiply_by_matrix(t_coord p, t_matrix m)
{
	t_coord	res;

	res.x = p.x * m.m[0][0] + p.y * m.m[1][0] + p.z * m.m[2][0] + m.m[3][0];
	res.y = p.x * m.m[0][1] + p.y * m.m[1][1] + p.z * m.m[2][1] + m.m[3][1];
	res.z = p.x * m.m[0][2] + p.y * m.m[1][2] + p.z * m.m[2][2] + m.m[3][2];
	return (res);
}

t_matrix	look_at(t_coord *origin, t_coord *cam_vector)
{
	t_matrix	m;
	t_coord		random;
	t_coord		right;
	t_coord		up;

	random = new_coord(0, 1, 0);
	if (cam_vector->x == 0 && cam_vector->z == 0)
		random = new_coord(1, 0, 0);
	right = cross_product(&random, cam_vector);
	vec_normalize(&right);
	up = cross_product(cam_vector, &right);
	vec_normalize(&up);
	m.m[0][0] = right.x;
	m.m[0][1] = right.y;
	m.m[0][2] = right.z;
	m.m[1][0] = up.x;
	m.m[1][1] = up.y;
	m.m[1][2] = up.z;
	m.m[2][0] = cam_vector->x;
	m.m[2][1] = cam_vector->y;
	m.m[2][2] = cam_vector->z;
	m.m[3][0] = origin->x;
	m.m[3][1] = origin->y;
	m.m[3][2] = origin->z;
	return (m);
}
