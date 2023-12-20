/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gseco-lu <gseco-lu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:16:49 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/20 12:05:05 by gseco-lu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

char	**ft_split_pop_back(char *str, char *set)
{
	char	**array;
	int		i;

	i = -1;
	while (str[++i])
	{
		if (ft_strchr(set, str[i]))
			str[i] = 1;
	}
	array = ft_split(str, 1);
	i = -1;
	return (array);
}

t_scene	*free_element(char *line, t_scene *scene)
{
	if (line)
	{
		free(line);
		return (NULL);
	}
	if (!scene->c)
	{
		free_scene(scene);
		return (NULL);
	}
	return (NULL);
}
