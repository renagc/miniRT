/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:06:48 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/30 09:35:25 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	print_coord(t_coord *coord)
{
	if (!coord)
		return ;
	printf("	coord_xyz: %f, %f, %f\n", coord->x, coord->y, coord->z);
}

static void	print_color(t_rgb *rgb)
{
	if (!rgb)
		return ;
	printf("	color_rgba: %d, %d, %d, %d\n", rgb->r, rgb->g, rgb->b, rgb->a);
}

static void	print_scene_camera(t_camera *camera)
{
	if (!camera)
		return ;
	printf("Camera ----------------------------------------------\n");
	printf("	FOV: %d\n", camera->fov);
	printf("	Position: ");
	print_coord(camera->pos);
	printf("	Orientation: ");
	print_coord(camera->ori);
}

static void	print_scene_amb_light(t_amb_light *amb_light)
{
	if (!amb_light)
		return ;
	printf("Ambient Light ---------------------------------------\n");
	printf("	ratio: %f\n", amb_light->ratio);
	print_color(amb_light->color);
}

static void	print_scene_light(t_light *light)
{
	if (!light)
		return ;
	printf("Lights ----------------------------------------------\n");
	printf("	Ratio: %f\n", light->ratio);
	printf("	Position: ");
	print_coord(light->pos);
}

static void	print_scene_spheres(t_sphere *sphere)
{
	t_sphere	*temp;
	int			i;

	temp = sphere;
	i = 0;
	if (!temp)
		return ;
	printf("Spheres ---------------------------------------------\n");
	while (temp)
	{
		printf("	Sphere[%d]\n", i);
		printf("		Position: ");
		print_coord(temp->pos);
		printf("		Color: ");
		print_color(temp->color);
		printf("		Diameter: %f\n", temp->d);
		i++;
		temp = temp->next;
	}
}

static void	print_scene_cylinders(t_cylinder *cylinder)
{
	t_cylinder	*temp;
	int			i;

	temp = cylinder;
	i = 0;
	if (!temp)
		return ;
	printf("Cylinders ---------------------------------------------\n");
	while (temp)
	{
		printf("	Cylinder[%d]\n", i);
		printf("		Position: ");
		print_coord(temp->pos);
		printf("		Color: ");
		print_color(temp->color);
		printf("		Diameter: %f\n", temp->d);
		printf("		Height: %f\n", temp->h);
		i++;
		temp = temp->next;
	}
}

static void	print_scene_planes(t_plane *plane)
{
	t_plane	*temp;
	int		i;

	temp = plane;
	i = 0;
	if (!temp)
		return ;
	printf("planes ---------------------------------------------\n");
	while (temp)
	{
		printf("	plane[%d]\n", i);
		printf("		Position: ");
		print_coord(temp->pos);
		printf("		Orientation: ");
		print_coord(temp->ori);
		printf("		Color: ");
		print_color(temp->color);
		i++;
		temp = temp->next;
	}
}

void	debug(t_scene *scene)
{
	if (!scene)
		return ;
	print_scene_amb_light(scene->a);
	print_scene_camera(scene->c);
	print_scene_light(scene->l);
	print_scene_spheres(scene->sp);
	print_scene_cylinders(scene->cy);
	print_scene_planes(scene->pl);
}
