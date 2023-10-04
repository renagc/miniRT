/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:50:53 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/04 16:14:58 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*sj;

	if (!s1 || !s2)
		return (0);
	sj = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!sj)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		sj[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		sj[i] = s2[j];
		i++;
		j++;
	}
	sj[i] = '\0';
	return (sj);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sp;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup("0"));
	if ((start + len) > ft_strlen(s))
		len = ft_strlen(s) - start;
	sp = malloc((len + 2) * sizeof(char));
	if (!sp)
		return (NULL);
	i = 0;
	while (s[start] != '\0' && i < len && start < ft_strlen(s))
	{
		sp[i] = s[start];
		i++;
		start++;
	}
	sp[i] = '\n';
	sp[i + 1] = '\0';
	return (sp);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*scpy;

	i = 0;
	while (s1[i] != '\0')
		i++;
	scpy = malloc(i * sizeof(char) + 1);
	if (!scpy)
		return (0);
	while (i >= 0)
	{
		scpy[i] = s1[i];
		i--;
	}
	return (scpy);
}

int	check_end_line(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
