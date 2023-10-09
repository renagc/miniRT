/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:55:21 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/06 16:08:54 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//this function delete last char of a string
void	ft_pop_back(char **str)
{
	char	*new;
	int		len;
	int		i;

	if (!(*str))
		return ;
	len = ft_strlen(*str);
	if (len == 1)
	{
		free(*str);
		return ;
	}
	new = malloc(len);
	if (!new)
		return ;
	i = -1;
	while (++i < len - 1)
		new[i] = (*str)[i];
	new[i] = '\0';
	free(*str);
	*str = new;
}
