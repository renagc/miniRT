/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:54:11 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/31 12:22:37 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_coord	rotation_axis(t_coord *temp_ori, double *dot_product)
{
	t_coord		forward;
	t_coord		rotation_axis;

	forward.x = 0.0;
	forward.y = 0.0;
	forward.z = 1.0;
	rotation_axis.x = forward.y * temp_ori->z - forward.z * temp_ori->y;
	rotation_axis.y = forward.z * temp_ori->x - forward.x * temp_ori->z;
	rotation_axis.z = forward.x * temp_ori->y - forward.y * temp_ori->x;
	*dot_product = forward.x * temp_ori->x + forward.y * temp_ori->y + forward.z * temp_ori->z;
	return (rotation_axis);
}

t_coord	matrix_x(t_coord *rotation_axis, double c, double s, double t)
{
	t_coord	matrix_x;

	matrix_x.x = t * rotation_axis->x * rotation_axis->x + c;
	matrix_x.y = t * rotation_axis->x * rotation_axis->y - s * rotation_axis->z;
	matrix_x.z = t * rotation_axis->x * rotation_axis->z + s * rotation_axis->y;
	return (matrix_x);
}

t_coord	matrix_y(t_coord *rotation_axis, double c, double s, double t)
{
	t_coord	matrix_y;

	matrix_y.x = t * rotation_axis->x * rotation_axis->y + s * rotation_axis->z;
	matrix_y.y = t * rotation_axis->y * rotation_axis->y + c;
	matrix_y.z = t * rotation_axis->y * rotation_axis->z - s * rotation_axis->x;
	return (matrix_y);
}

t_coord	matrix_z(t_coord *rotation_axis, double c, double s, double t)
{
	t_coord	matrix_z;

	matrix_z.x = t * rotation_axis->x * rotation_axis->z - s * rotation_axis->y;
	matrix_z.y = t * rotation_axis->y * rotation_axis->z + s * rotation_axis->x;
	matrix_z.z = t * rotation_axis->z * rotation_axis->z + c;
	return (matrix_z);
}

t_coord	rotate_vector(t_coord vector, t_coord rotation)
{
    double cosX = cos(rotation.x);
    double sinX = sin(rotation.x);
    double cosY = cos(rotation.y);
    double sinY = sin(rotation.y);
    double cosZ = cos(rotation.z);
    double sinZ = sin(rotation.z);

    t_coord rotated;
    rotated.x = vector.x * (cosY * cosZ) - vector.y * (cosX * sinZ - sinX * sinY * cosZ) + vector.z * (sinX * sinZ + cosX * sinY * cosZ);
    rotated.y = vector.x * (cosY * sinZ) + vector.y * (cosX * cosZ + sinX * sinY * sinZ) + vector.z * (sinX * cosZ - cosX * sinY * sinZ);
    rotated.z = -vector.x * sinY + vector.y * (sinX * cosY) + vector.z * (cosX * cosY);

    return (rotated);
}

t_matrix	create_rotation_matrix(t_coord *ori)
{
	double		dot_product;
	t_matrix	matrix;
	t_coord		rot_axis;
	t_coord		temp_ori;
	double		angle;
	double		c;
	double		s;

	temp_ori.x = ori->x;
	temp_ori.y = ori->y;
	temp_ori.z = ori->z;
	vec_normalize(&temp_ori);
	rot_axis = rotation_axis(&temp_ori, &dot_product);
	angle = acos(dot_product);
	c = cos(angle);
	s = sin(angle);
	matrix.x = matrix_x(&rot_axis, c, s, 1.0 - c);
	matrix.y = matrix_y(&rot_axis, c, s, 1.0 - c);
	matrix.z = matrix_z(&rot_axis, c, s, 1.0 - c);
	return (matrix);
}

t_coord	rotate_camera(t_coord orientation_vector, t_matrix rotation_matrix)
{
	t_coord	rotated;

	rotated.x = rotation_matrix.x.x * orientation_vector.x + rotation_matrix.x.y * orientation_vector.y + rotation_matrix.x.z * orientation_vector.z;
	rotated.y = rotation_matrix.y.x * orientation_vector.x + rotation_matrix.y.y * orientation_vector.y + rotation_matrix.y.z * orientation_vector.z;
	rotated.z = rotation_matrix.z.x * orientation_vector.x + rotation_matrix.z.y * orientation_vector.y + rotation_matrix.z.z * orientation_vector.z;
	return (rotated);
}
