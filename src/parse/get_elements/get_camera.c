/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:36:18 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/18 09:39:25 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int	is_fov(char *str)
{
	int	i;

	if (ft_strlen(str) > 3)
		return (0);
	i = -1;
	while (str && str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	if (ft_atoi(str) <= 0 || ft_atoi(str) > 180)
		return (0);
	return (1);
}

int	is_vector(t_coord *coord)
{
	if (coord->x < -1.0 || coord->x > 1.0)
		return (0);
	else if (coord->y < -1.0 || coord->y > 1.0)
		return (0);
	else if (coord->z < -1.0 || coord->z > 1.0)
		return (0);
	return (1);
}

t_camera	*get_camera(char **array)
{
	t_camera	*new;

	if (ft_arraylen(array) != 3)
		return (NULL);
	new = malloc(sizeof(t_camera));
	if (!new)
		return (NULL);
	if (!set_coord(array[0], &new->pos) || !set_coord(array[1], &new->ori))
	{
		free(new);
		return (NULL);
	}
	if (!is_vector(&new->ori) || !is_fov(array[2]))
	{
		free(new);
		return (NULL);
	}
	new->fov = ft_atoi(array[2]);
	return (new);
}
