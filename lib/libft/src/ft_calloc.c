/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:27:53 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/04 16:14:12 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*s;
	size_t	i;

	i = 0;
	s = malloc(count * size);
	if (!s)
		return (0);
	while (i < (count * size))
	{
		((char *)s)[i] = 0;
		i++;
	}
	return (s);
}
