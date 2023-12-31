/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:15:46 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/14 12:43:43 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_cylinder	*new_cy(char **array)
{
	t_cylinder	*new;

	if (ft_arraylen(array) != 5)
		return (NULL);
	new = malloc(sizeof(t_cylinder));
	if (!new)
		return (NULL);
	new->pos = get_coord(array[0]);
	new->ori = get_coord(array[1]);
	if (!new->pos || !is_coord(new->ori) || !new->ori
		|| !is_double(array[2]) || !is_double(array[3]))
	{
		free(new);
		return (NULL);
	}
	new->d = ft_atoi_dbl(array[2]);
	new->h = ft_atoi_dbl(array[3]);
	new->color = get_rgb(array[4]);
	if (!new->color || new->d <= 0 || new->h <= 0)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

int	get_cy(t_cylinder **cy_lst, char **array)
{
	t_cylinder	*temp;

	temp = *cy_lst;
	if (!temp)
	{
		*cy_lst = new_cy(array);
		if (!(*cy_lst))
			return (0);
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_cy(array);
		if (!temp->next)
			return (0);
	}
	return (1);
}
