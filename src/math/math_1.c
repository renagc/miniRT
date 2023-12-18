/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:04:23 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/18 12:05:22 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	vec_normalize(t_coord *vec)
{
	double	length;

	length = vec_length(vec);
	(*vec).x /= length;
	(*vec).y /= length;
	(*vec).z /= length;
}

double	product(t_coord *coord1, t_coord *coord2)
{
	double	result;

	result = coord1->x * coord2->x;
	result += coord1->y * coord2->y;
	result += coord1->z * coord2->z;
	return (result);
}

t_coord	new_coord(double x, double y, double z)
{
	t_coord	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

t_coord	cross(t_coord *a, t_coord *b)
{
	t_coord	c;

	c.x = a->y * b->z + b->y * a->z;
	c.y = a->x * b->z + b->x * a->z;
	c.z = a->x * b->y + a->y * b->x;
	return (c);
}
