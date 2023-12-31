/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:21:34 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/06 20:03:02 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	*sp;
	unsigned char	cp;

	sp = (unsigned char *)s;
	cp = (unsigned char)c;
	i = 0;
	while (sp && sp[i])
	{
		if (sp[i] == cp)
			break ;
		i++;
	}
	if (sp && sp[i] == cp)
		return ((char *)sp + i);
	return (0);
}
