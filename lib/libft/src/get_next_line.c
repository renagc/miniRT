/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 09:23:43 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/04 16:14:58 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_end_of_file(char **line, char ***str)
{
	if ((***str) != '\0')
		*line = ft_strdup((**str));
	else
		*line = 0;
	free(**str);
	**str = 0;
}

static char	*ft_get_line(char **str, int char_read, char **buf)
{
	int		i;
	char	*str_temp;
	char	*line;

	i = 0;
	if (char_read <= 0 && !(*str))
	{
		free(*buf);
		*buf = NULL;
		return (NULL);
	}
	while ((*str)[i] != '\0' && (*str)[i] != '\n')
		i++;
	if ((*str)[i] == '\n')
	{
		line = ft_substr((*str), 0, i);
		str_temp = ft_strdup(&((*str)[i + 1]));
		free(*str);
		*str = str_temp;
	}
	else
		ft_end_of_file(&line, &str);
	free((*buf));
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*temp;
	char		*buf;
	int			char_read;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	char_read = read (fd, buf, BUFFER_SIZE);
	while (char_read > 0)
	{
		buf[char_read] = '\0';
		if (!stash)
			stash = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(stash, buf);
			free(stash);
			stash = temp;
		}
		if (check_end_line(stash))
			break ;
		char_read = read (fd, buf, BUFFER_SIZE);
	}
	return (ft_get_line(&stash, char_read, &buf));
}
