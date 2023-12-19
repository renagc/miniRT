/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qwerty <qwerty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:02:28 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/19 16:30:44 by qwerty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	exit_program(char *error_msg, t_scene *scene)
{
	if (error_msg)
	{
		ft_putstr_fd(error_msg, 2);
		ft_putstr_fd("\n", 2);
	}
	if (scene)
	{
		free_scene(scene);
	}
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
		exit_program("This program only take 2 arguments", *scene);
	if (check_file_name(av[1]))
		exit_program("Filename not valid", *scene);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit_program("File not found", *scene);
	*scene = get_scene(fd);
	close(fd);
	if (!(*scene))
		exit_program("Scene Error", *scene);
}
