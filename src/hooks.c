/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:03:07 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/18 21:03:13 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	ft_xbutton(t_scene *scene)
{
	free_scene(scene);
	return (0);
}

int	ft_escbutton(int key, t_scene *scene)
{
	if (key == KEY_ESC)
		free_scene(scene);
	return (1);
}
