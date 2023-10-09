/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:15:46 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/09 12:34:08 by rgomes-c         ###   ########.fr       */
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
	new->pos = get_vector(array[0]);
	new->ori = get_vector(array[1]);
	if (!new->pos || !new->ori || !is_vector(new->ori))
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
	new->next = NULL;
	return (new);
}

int	get_pl(t_plane **pl_lst, char **array)
{
	t_plane	*temp;

	temp = *pl_lst;
	if (!temp)
	{
		*pl_lst = new_pl(array);
		if (!(*pl_lst))
			return (0);
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_pl(array);
		if (!temp->next)
			return (0);
	}
	return (1);
}
