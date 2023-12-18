/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:18:56 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/18 11:23:08 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static bool	is_rgb(char *str)
{
	int	i;

	if (ft_strlen(str) > 3)
		return (false);
	i = -1;
	while (str && str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
	}
	if (ft_atoi(str) > 255)
		return (false);
	return (true);
}

bool	set_color(char *str, t_rgb *rgb)
{
	t_rgb	temp;
	char	**array;
	int		i;

	i = -1;
	array = ft_split_pop_back(str, ",");
	if (!array)
		return (NULL);
	while (array[++i])
	{
		if (!is_rgb(array[i]) || ft_arraylen(array) != 3)
		{
			free_array(array);
			return (false);
		}
	}
	temp.r = ft_atoi(array[0]);
	temp.g = ft_atoi(array[1]);
	temp.b = ft_atoi(array[2]);
	free_array(array);
	*rgb = temp;
	return (true);
}

int	is_double(char *str)
{
	int		i;
	bool	point;

	i = 0;
	point = false;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '.' || str[ft_strlen(str) - 1] == '.')
		return (0);
	while (str[i])
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

bool	set_coord(char *str, t_coord *coord)
{
	char	**array;

	array = ft_split_pop_back(str, ",");
	if (!array)
		return (false);
	if (ft_arraylen(array) != 3)
	{
		free_array(array);
		return (false);
	}
	if (!is_double(array[0]) || !is_double(array[1]) || !is_double(array[2]))
	{
		free_array(array);
		return (false);
	}
	*coord = new_coord(ft_atod(array[0]), ft_atod(array[1]), ft_atod(array[2]));
	free_array(array);
	return (true);
}
