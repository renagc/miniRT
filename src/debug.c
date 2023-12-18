/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:06:48 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/18 10:09:40 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	print_coord(t_coord *coord)
{
	if (!coord)
		return ;
	printf("%f, %f, %f\n", coord->x, coord->y, coord->z);
}

static void	print_color(t_rgb *rgb)
{
	if (!rgb)
		return ;
	printf("%d, %d, %d\n", rgb->r, rgb->g, rgb->b);
}

static void	print_scene_camera(t_camera *camera)
{
	if (!camera)
		return ;
	printf("Camera ----------------------------------------------\n");
	printf("	FOV: %d\n", camera->fov);
	printf("	Position: ");
	print_coord(&camera->pos);
	printf("	Orientation: ");
	print_coord(&camera->ori);
}

static void	print_scene_amb_light(t_amb_light *amb_light)
{
	if (!amb_light)
	{
		printf("No ambient light\n");
		return ;
	}
	printf("Ambient Light ---------------------------------------\n");
	printf("	ratio: %f\n", amb_light->ratio);
	print_color(&amb_light->color);
}

static void	print_scene_light(t_light *light)
{
	if (!light)
		return ;
	printf("	Ratio: %f\n", light->ratio);
	printf("	Position: ");
	print_coord(&light->pos);
}

static void	print_sphere(t_sphere *sphere)
{
	printf(" \033[0;31mSphere\n\n");
	printf("  Position: ");
	print_coord(&sphere->pos);
	printf("  Color: ");
	print_color(&sphere->color);
	printf("  Diameter: %f\n", sphere->d);
	printf("\033[0m\n");
}

static void	print_cylinder(t_cylinder *cylinder)
{
	printf(" \033[0;33mCylinder\n\n");
	printf("  Position: ");
	print_coord(&cylinder->pos);
	printf("  Vector: ");
	print_coord(&cylinder->ori);
	printf("  Color: ");
	print_color(&cylinder->color);
	printf("  Diameter: %f\n", cylinder->d);
	printf("  Height: %f\n", cylinder->h);
	printf("\033[0m\n");
}

static void	print_plane(t_plane *plane)
{
	printf(" \033[0;34mPlane\n\n");
	printf("  Position: ");
	print_coord(&plane->pos);
	printf("  Orientation: ");
	print_coord(&plane->ori);
	printf("  Color: ");
	print_color(&plane->color);
	printf("\033[0m\n");
}

void	print_objects(t_object *obj)
{
	t_object	*temp;
	int			i;

	i = -1;
	printf("Objects ----------------------------------------------\n\n");
	temp = obj;
	while (temp)
	{
		printf("Object[%d]:", ++i);
		if (temp->type == SP)
			print_sphere(temp->data);
		else if (temp->type == PL)
			print_plane(temp->data);
		else if (temp->type == CY)
			print_cylinder(temp->data);
		temp = temp->next;
	}
}

void	debug(t_scene *scene)
{
	if (!scene)
	{
		printf("No scene to debug\n");
		return ;
	}
	print_scene_amb_light(scene->a);
	print_scene_camera(scene->c);
	print_scene_light(scene->l);
	print_objects(scene->obj);
}
