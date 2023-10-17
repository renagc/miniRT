/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:32:55 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/14 12:27:15 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int	is_ratio(char *str)
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
			return (0);
		else if (!point && str[i] == '.')
			point = true;
		else if (point && str[i] == '.')
			return (0);
		i++;
	}
	return (1);
}

static double	get_ratio(char *str)
{
	double	min;
	double	max;
	double	n;

	min = 0.0;
	max = 1.0;
	n = ft_atoi_dbl(str);
	if (n >= min && n <= max)
		return (n);
	return (-1);
}

t_light	*get_light(char **array)
{
	t_light	*light;

	if (ft_arraylen(array) != 2 && ft_arraylen(array) != 3)
		return (NULL);
	if (!is_ratio(array[1]))
		return (NULL);
	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->pos = get_coord(array[0]);
	if (!light->pos)
	{
		free(light);
		return (NULL);
	}
	light->ratio = get_ratio(array[1]);
	if (light->ratio < 0)
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
	if (!is_ratio(array[0]))
		return (NULL);
	amb = malloc(sizeof(t_amb_light));
	if (!amb)
		return (NULL);
	amb->ratio = get_ratio(array[0]);
	if (amb->ratio < 0)
	{
		free(amb);
		return (NULL);
	}
	amb->color = get_rgb(array[1]);
	if (!amb->color)
	{
		free(amb);
		return (NULL);
	}
	return (amb);
}
