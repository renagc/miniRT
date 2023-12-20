/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gseco-lu <gseco-lu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:03:07 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/20 12:03:18 by gseco-lu         ###   ########.fr       */
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
