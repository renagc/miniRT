/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:19:04 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/09 12:29:14 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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

t_vector	*get_vector(char *str)
{
	t_vector	*xyz;
	char		**array;

	array = ft_split_pop_back(str, ",");
	if (!array)
		return (NULL);
	xyz = malloc(sizeof(t_vector));
	if (!xyz || ft_arraylen(array) != 3)
	{
		if (xyz)
			free(xyz);
		free_array(array);
		return (NULL);
	}
	if (!is_double(array[0]) || !is_double(array[1]) || !is_double(array[2]))
	{
		free(xyz);
		free_array(array);
		return (NULL);
	}
	xyz->x = ft_atoi_dbl(array[0]);
	xyz->y = ft_atoi_dbl(array[1]);
	xyz->z = ft_atoi_dbl(array[2]);
	free(array);
	return (xyz);
}
