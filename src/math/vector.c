/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qwerty <qwerty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:51:14 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/19 17:33:38 by qwerty           ###   ########.fr       */
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

t_vector	vec_normalize(t_vector *vec)
{
	double		length;
	t_vector	tmp;

	length = vec_length(vec);
	tmp.x = vec->x / length;
	tmp.y = vec->y / length;
	tmp.z = vec->z / length;
	return (tmp);
}

double	product(t_vector *vec1, t_vector *vec2)
{
	double	result;

	result = vec1->x * vec2->x;
	result += vec1->y * vec2->y;
	result += vec1->z * vec2->z;
	return (result);
}

t_vector	find_p(t_vector *vec1, t_coord *coord1, double x)
{
	t_vector	p;

	p.x = vec1->x * x + coord1->x;
	p.y = vec1->y * x + coord1->y;
	p.z = vec1->z * x + coord1->z;
	return (p);
}
