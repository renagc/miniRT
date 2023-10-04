/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:14:29 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/04 16:14:12 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*sp;

	sp = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (sp[i] == (unsigned char)c)
			return (sp + i);
		i++;
	}
	return (NULL);
}
