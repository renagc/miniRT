/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qwerty <qwerty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:15:46 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/17 16:35:54 by qwerty           ###   ########.fr       */
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
	new->next = NULL;
	new->pos = get_coord(array[0]);
	if (!new->pos || !is_double(array[1]) || ft_atoi_dbl(array[1]) <= 0)
	{
		free(new);
		return (NULL);
	}
	new->d = ft_atoi_dbl(array[1]);
	new->color = get_rgb(array[2]);
	if (!new->color)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

int	get_sp(t_sphere **sp_lst, char **array)
{
	t_sphere	*temp;

	temp = *sp_lst;
	if (!temp)
	{
		*sp_lst = new_sp(array);
		if (!(*sp_lst))
			return (0);
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_sp(array);
		if (!temp->next)
			return (0);
	}
	return (1);
}
