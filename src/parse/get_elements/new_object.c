/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:35:54 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/18 09:39:25 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_sphere	*new_sp(char **array)
{
	t_sphere	*new;

	if (ft_arraylen(array) != 3)
		return (NULL);
	new = malloc(sizeof(t_sphere));
	if (!new)
		return (NULL);
	if (!set_coord(array[0], &new->pos) || !is_double(array[1]))
	{
		free(new);
		return (NULL);
	}
	new->d = ft_atod(array[1]);
	if (!set_color(array[2], &new->color) || new->d <= 0)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

t_plane	*new_pl(char **array)
{
	t_plane	*new;

	if (ft_arraylen(array) != 3)
		return (NULL);
	new = malloc(sizeof(t_plane));
	if (!new)
		return (NULL);
	if (!set_coord(array[0], &new->pos) || !set_coord(array[1], &new->ori))
	{
		free(new);
		return (NULL);
	}
	if (!is_vector(&new->ori) || !set_color(array[2], &new->color))
	{
		free(new);
		return (NULL);
	}
	vec_normalize(&new->ori);
	return (new);
}

t_cylinder	*new_cy(char **array)
{
	t_cylinder	*new;

	if (ft_arraylen(array) != 5)
		return (NULL);
	new = malloc(sizeof(t_cylinder));
	if (!new)
		return (NULL);
	if (!set_coord(array[0], &new->pos) || !set_coord(array[1], &new->ori))
	{
		free(new);
		return (NULL);
	}
	if (!is_vector(&new->ori) || !is_double(array[2]) || !is_double(array[3]))
	{
		free(new);
		return (NULL);
	}
	new->d = ft_atod(array[2]);
	new->h = ft_atod(array[3]);
	if (!set_color(array[4], &new->color) || new->d <= 0 || new->h <= 0)
	{
		free(new);
		return (NULL);
	}
	return (new);
}
