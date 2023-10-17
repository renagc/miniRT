/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:02:28 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/10 12:08:39 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	error_parse(char *display_error)
{
	ft_putstr_fd(display_error, 2);
	ft_putstr_fd("\n", 2);
}

static void	exit_parse(char *display_error)
{
	if (display_error)
		error_parse(display_error);
	exit(1);
}

//function testes, return 1 if the file isn't *.rt
static int	check_file_name(char *str)
{
	int	len;

	if (!str)
		return (1);
	len = ft_strlen(str);
	while (--len && str[len])
	{
		if (str[len] == '.')
			break ;
	}
	if (str[len] != '.')
		return (1);
	if (!ft_strcmp(&str[len + 1], "rt"))
		return (0);
	return (1);
}

void	parse(int ac, char **av, t_scene **scene)
{
	int		fd;

	if (ac != 2)
		exit_parse("This program only take 2 arguments");
	if (check_file_name(av[1]))
		exit_parse("Filename not valid");
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		exit(1);
	}
	*scene = get_scene(fd);
	if (!scene)
	{
		close(fd);
		exit_parse("Scene Error");
	}
	close(fd);
}
