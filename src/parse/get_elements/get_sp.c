/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:15:46 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/09 15:08:47 by rgomes-c         ###   ########.fr       */
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
	new->pos = get_vector(array[0]);
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
	new->next = NULL;
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
