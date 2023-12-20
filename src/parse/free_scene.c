/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gseco-lu <gseco-lu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:48:56 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/20 12:03:32 by gseco-lu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	free_mlx(t_mlx *mlx)
{
	if (mlx->img.reference)
		mlx_destroy_image(mlx->ref, mlx->img.reference);
	if (mlx->ref)
		mlx_destroy_window(mlx->ref, mlx->win);
	if (mlx->ref)
	{
		mlx_destroy_display(mlx->ref);
		free(mlx->ref);
	}
}

void	free_scene(t_scene *scene)
{
	t_object	*next;

	next = NULL;
	if (!scene)
		return ;
	if (scene && scene->a)
		free(scene->a);
	if (scene && scene->c)
		free(scene->c);
	if (scene && scene->l)
	{
		free(scene->l);
	}
	if (scene->obj)
		next = scene->obj->next;
	while (scene && scene->obj)
	{
		next = scene->obj->next;
		free(scene->obj->data);
		free(scene->obj);
		scene->obj = next;
	}
	free_mlx(&scene->mlx);
	free(scene);
}
