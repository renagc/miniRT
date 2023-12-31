/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:16:49 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/09 12:27:19 by rgomes-c         ###   ########.fr       */
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
	while (array[++i])
		ft_pop_back(&array[i]);
	return (array);
}
