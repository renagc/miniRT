/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qwerty <qwerty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 23:48:56 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/17 16:45:34 by qwerty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	free_capital(t_scene *scene)
{
	if (scene->a)
	{
		free(scene->a->color);
		free(scene->a);
	}
	if (scene->c)
	{
		free(scene->c->pos);
		free(scene->c->ori);
		free(scene->c);
	}
	if (scene->l)
	{
		free(scene->l->pos);
		free(scene->l);
	}
}

static void	free_sp(t_sphere *sphere)
{
	t_sphere	*curr;
	t_sphere	*next;

	curr = sphere;
	
	while (curr)
	{
		if (curr->next)
			next = curr->next;
		free(curr->pos);
		free(curr->color);
		free(curr);
		curr = next;
	}
}

static void	free_pl(t_plane *plane)
{
	t_plane	*curr;
	t_plane	*next;

	curr = plane;
	
	while (curr)
	{
		if (curr->next)
			next = curr->next;
		free(curr->pos);
		free(curr->color);
		free(curr->ori);
		free(curr);
		curr = next;
	}
}

static void	free_cy(t_cylinder *cylinder)
{
	t_cylinder	*curr;
	t_cylinder	*next;

	curr = cylinder;
	
	while (curr)
	{
		if (curr->next)
			next = curr->next;
		free(curr->color);
		free(curr->ori);
		free(curr->pos);
		free(curr);
		curr = next;
	}
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free_capital(scene);
	if (scene->sp)
		free_sp(scene->sp);
	if (scene->pl)
		free_pl(scene->pl);
	if (scene->cy)
		free_cy(scene->cy);
	free(scene);
}
