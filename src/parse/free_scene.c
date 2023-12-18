/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:48:56 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/18 09:35:04 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	free_mlx(t_mlx *mlx)
{
	if (mlx->ref)
		mlx_destroy_window(mlx->ref, mlx->win);
}

void	free_scene(t_scene *scene)
{
	t_object	*next;

	if (!scene)
		return ;
	if (scene->a)
		free(scene->a);
	if (scene->c)
		free(scene->c);
	if (scene->l)
		free(scene->l);
	next = scene->obj->next;
	while (scene->obj)
	{
		if (scene->obj->data)
			free(scene->obj->data);
		free(scene->obj);
		scene->obj = next;
		next = scene->obj->next;
	}
	free_mlx(&scene->mlx);
	free(scene);
}
