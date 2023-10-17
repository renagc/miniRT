/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:51:14 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/17 14:52:01 by rgomes-c         ###   ########.fr       */
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

double	vec_length(t_vector *vec)
{
	double	result;

	result = sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));
	return (result);
}

void	vec_normalize(t_vector *vec)
{
	double	length;

	length = vec_length(vec);
	vec->x /= length;
	vec->y /= length;
	vec->z /= length;
}

double	product(t_coord *coord1, t_coord *coord2)
{
	double	result;

	result = coord1->x * coord2->x;
	result += coord1->y * coord2->y;
	result += coord1->z * coord2->z;
	return (result);
}
