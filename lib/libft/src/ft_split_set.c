/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:59:42 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/09 12:07:55 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_split_set(char *str, char *set)
{
	int		i;

	if (!str || !set)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (ft_strchr(set, str[i]))
			str[i] = set[0];
	}
	return (ft_split((char *)str, set[0]));
}