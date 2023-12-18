/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:15:52 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/18 16:39:20 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// Function to transform a 3D point using a transformation matrix
t_coord	transform_point(t_coord point, double matrix[4][4])
{
	t_coord	result;

	result.x = matrix[0][0] * point.x + matrix[0][1] * point.y \
		+ matrix[0][2] * point.z + matrix[0][3];
	result.y = matrix[1][0] * point.x + matrix[1][1] * point.y \
		+ matrix[1][2] * point.z + matrix[1][3];
	result.z = matrix[2][0] * point.x + matrix[2][1] * point.y \
		+ matrix[2][2] * point.z + matrix[2][3];
	return (result);
}

// Function to transform a 3D direction vector using a transformation matrix
t_coord	transform_direction(t_coord direction, double matrix[4][4])
{
	t_coord	result;

	result.x = matrix[0][0] * direction.x + matrix[0][1] * direction.y \
		+ matrix[0][2] * direction.z;
	result.y = matrix[1][0] * direction.x + matrix[1][1] * direction.y \
		+ matrix[1][2] * direction.z;
	result.z = matrix[2][0] * direction.x + matrix[2][1] * direction.y \
		+ matrix[2][2] * direction.z;
	return (result);
}
