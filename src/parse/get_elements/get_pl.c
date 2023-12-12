/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:15:46 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/11/28 16:34:05 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_plane	*new_pl(char **array)
{
	t_plane	*new;

	if (ft_arraylen(array) != 3)
		return (NULL);
	new = malloc(sizeof(t_plane));
	if (!new)
		return (NULL);
	new->pos = get_coord(array[0]);
	new->ori = get_coord(array[1]);
	if (!new->pos || !new->ori || !is_coord(new->ori))
	{
		free(new);
		return (NULL);
	}
	new->color = get_rgb(array[2]);
	if (!new->color)
	{
		free(new);
		return (NULL);
	}
	vec_normalize(new->ori);
	return (new);
}
