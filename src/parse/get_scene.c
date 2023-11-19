/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:18:27 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/11/17 18:13:10 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	get_capital_element(t_scene *scene, char **array, int *flag)
{
	if (!ft_strcmp(array[0], "A") && !scene->a)
	{
		scene->a = get_amb_light(&array[1]);
		if (!scene->a)
			*flag = 0;
	}
	else if (!ft_strcmp(array[0], "C") && !scene->c)
	{
		scene->c = get_camera(&array[1]);
		if (!scene->c)
			*flag = 0;
	}
	else if (!ft_strcmp(array[0], "L") && !scene->l)
	{
		scene->l = get_light(&array[1]);
		if (!scene->l)
			*flag = 0;
	}
	else
		*flag = -1;
}

bool	get_obj(int type, t_scene *scene, void	*obj_data)
{
	t_object	*temp;

	if (!scene->obj)
	{
		scene->obj = malloc(sizeof(t_object));
		if (!scene->obj)
			return (false);
		scene->obj->type = type;
		scene->obj->data = obj_data;
		scene->obj->next = NULL;
	}
	else
	{
		temp = scene->obj;
		while (temp->next)
			temp = temp->next;
		temp->next = malloc(sizeof(t_object));
		if (!temp->next)
			return (false);
		temp->next->type = type;
		temp->next->data = obj_data;
		temp->next->next = NULL;
	}
	return (scene->obj->data != NULL);
}

static void	get_double_element(t_scene *scene, char **array, int *flag)
{
	if (!ft_strcmp(array[0], "sp"))
	{
		if (!get_obj(SPHERE, scene, new_sp(&array[1])))
			*flag = 0;
	}
	else if (!ft_strcmp(array[0], "pl"))
	{
		if (!get_obj(PLANE, scene, new_pl(&array[1])))
			*flag = 0;
	}
	else if (!ft_strcmp(array[0], "cy"))
	{
		if (!get_obj(CYLINDER, scene, new_cy(&array[1])))
			*flag = 0;
	}
	else
		*flag = -1;
}

static int	get_element(t_scene *scene, char **array)
{
	int	capital_flag;
	int	double_flag;

	capital_flag = 1;
	double_flag = 1;
	if (array && !array[0])
		return (1);
	get_capital_element(scene, array, &capital_flag);
	if (capital_flag == 0)
		return (0);
	else if (capital_flag == -1)
	{
		get_double_element(scene, array, &double_flag);
		if (double_flag == 0)
			return (0);
		else if (double_flag == -1)
			return (0);
	}
	return (1);
}

t_scene	*handle_free_scene(char *line, char **element, t_scene *scene)
{
	if (line)
		free(line);
	if (scene)
		free(scene);
	if (element)
		free_array(element);
	return (NULL);
}

t_scene	*get_scene(int fd)
{
	t_scene	*scene;
	char	*line;
	char	**element;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->a = NULL;
	scene->c = NULL;
	scene->l = NULL;
	scene->obj = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		element = ft_split_pop_back(line, " \t\n");
		if (!element || !get_element(scene, element))
			return (handle_free_scene(line, element, scene));
		free(line);
		free_array(element);
	}
	return (scene);
}
