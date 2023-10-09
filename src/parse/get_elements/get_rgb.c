/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:08:18 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/09 12:10:21 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int	is_rgb(char *str)
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
	if (ft_atoi(str) > 255)
		return (0);
	return (1);
}

t_rgb	*get_rgb(char *str)
{
	t_rgb	*rgb;
	char	**array;

	array = ft_split_pop_back(str, ",");
	if (!array)
		return (NULL);
	rgb = malloc(sizeof(t_rgb));
	if (!rgb || ft_arraylen(array) != 3)
	{
		if (rgb)
			free(rgb);
		free_array(array);
		return (NULL);
	}
	if (!is_rgb(array[0]) || !is_rgb(array[1]) || !is_rgb(array[2]))
	{
		free(rgb);
		free_array(array);
		return (NULL);
	}
	rgb->r = ft_atoi(array[0]);
	rgb->g = ft_atoi(array[1]);
	rgb->b = ft_atoi(array[2]);
	free(array);
	return (rgb);
}
