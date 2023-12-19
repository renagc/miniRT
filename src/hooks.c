/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qwerty <qwerty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:03:07 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/19 16:42:10 by qwerty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	ft_xbutton(t_scene *scene)
{
	if (scene)
	{
		free_scene(scene);
		exit(0);
	}
	return (0);
}

int	ft_escbutton(int key, t_scene *scene)
{
	if (key == KEY_ESC)
	{
		free_scene(scene);
		exit(0);
	}
	return (1);
}
