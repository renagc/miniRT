/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qwerty <qwerty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:32:55 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/19 16:47:40 by qwerty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static bool	is_ratio(char *str)
{
	int		i;
	bool	point;

	i = 0;
	point = false;
	if (str[i] == '.' || str[ft_strlen(str) - 1] == '.')
		return (0);
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (false);
		else if (!point && str[i] == '.')
			point = true;
		else if (point && str[i] == '.')
			return (false);
		i++;
	}
	return (true);
}

static bool	set_ratio(char *str, double *ratio)
{
	*ratio = ft_atod(str);
	if (is_ratio(str) && *ratio >= 0.0 && *ratio <= 1.0)
		return (true);
	return (false);
}

t_light	*get_light(char **array)
{
	t_light	*light;

	if (ft_arraylen(array) != 2)
		return (NULL);
	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	if (!set_coord(array[0], &light->pos))
	{
		free(light);
		return (NULL);
	}
	if (!set_ratio(array[1], &light->ratio) || light->ratio < 0)
	{
		free(light);
		return (NULL);
	}
	return (light);
}

t_amb_light	*get_amb_light(char **array)
{
	t_amb_light	*amb;

	if (ft_arraylen(array) != 2)
		return (NULL);
	amb = malloc(sizeof(t_amb_light));
	if (!amb)
		return (NULL);
	if (!set_ratio(array[0], &(amb->ratio)))
	{
		free(amb);
		return (NULL);
	}
	else if (!set_color(array[1], &(amb->color)))
	{
		free(amb);
		return (NULL);
	}
	return (amb);
}
