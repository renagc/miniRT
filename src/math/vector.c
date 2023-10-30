/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:51:14 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/30 16:37:53 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vector	subtract(t_coord *coord1, t_coord *coord2)
{
	t_vector	result;

	result.x = coord1->x - coord2->x;
	result.y = coord1->y - coord2->y;
	result.z = coord1->z - coord2->z;
	return (result);
}

t_coord	subtract_const(t_coord *coord1, t_coord *coord2, double constant)
{
	t_coord	result;

	result.x = coord1->x - constant * coord2->x;
	result.y = coord1->y - constant * coord2->y;
	result.z = coord1->z - constant * coord2->z;
	return (result);
}

t_coord	add_const(t_coord *coord1, t_coord *coord2, double constant)
{
	t_coord	result;

	result.x = coord1->x + (constant * coord2->x);
	result.y = coord1->y + (constant * coord2->y);
	result.z = coord1->z + (constant * coord2->z);
	return (result);
}

double	vec_length(t_coord *vec)
{
	double	result;

	result = sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));
	return (result);
}

t_rgb	*multiply_color(t_rgb *color, double multiply)
{
	t_rgb	*result;

	result = malloc(sizeof(t_rgb));
	result->r = color->r * multiply;
	result->g = color->g * multiply;
	result->b = color->b * multiply;
	result->a = color->a * multiply;
	return (result);
}

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
