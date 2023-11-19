/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:06:48 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/11/19 11:39:03 by rgomes-c         ###   ########.fr       */
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
	printf("	Sphere:\n");
	printf("		Position: ");
	print_coord(sphere->pos);
	printf("		Color: ");
	print_color(sphere->color);
	printf("		Diameter: %f\n", sphere->d);
}

static void	print_scene_cylinders(t_cylinder *cylinder)
{
	printf("Cylinders ---------------------------------------------\n");
	printf("	Cylinder:\n");
	printf("		Position: ");
	print_coord(cylinder->pos);
	printf("		Color: ");
	print_color(cylinder->color);
	printf("		Diameter: %f\n", cylinder->d);
	printf("		Height: %f\n", cylinder->h);
}

static void	print_scene_planes(t_plane *plane)
{
	printf("planes ---------------------------------------------\n");
	printf("		Position: ");
	print_coord(plane->pos);
	printf("		Orientation: ");
	print_coord(plane->ori);
	printf("		Color: ");
	print_color(plane->color);
}

void	print_objects(t_object *obj)
{
	t_object	*temp;

	temp = obj;
	while (temp)
	{
		if (temp->type == SPHERE)
			print_scene_spheres(temp->data);
		else if (temp->type == PLANE)
			print_scene_planes(temp->data);
		else if (temp->type == CYLINDER)
			print_scene_cylinders(temp->data);
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
	print_objects(scene->obj);
}
