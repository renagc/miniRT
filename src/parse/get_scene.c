/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gseco-lu <gseco-lu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:18:27 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/20 12:03:29 by gseco-lu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

bool	get_el(int name, t_scene *scene, char **array)
{
	if (name == A)
	{
		scene->a = get_amb_light(array);
		if (!scene->a)
			return (false);
	}
	else if (name == C)
	{
		scene->c = get_camera(array);
		if (!scene->c)
			return (false);
	}
	else if (name == L)
	{
		scene->l = get_light(array);
		if (!scene->l)
			return (false);
	}
	else
		return (false);
	return (true);
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
	return (obj_data);
}

static int	find_element_name(char **array, t_scene *scene)
{
	if (!array[0])
		return (-2);
	if (!ft_strcmp(array[0], "A") && !scene->a)
		return (A);
	else if (!ft_strcmp(array[0], "C") && !scene->c)
		return (C);
	else if (!ft_strcmp(array[0], "L") && !scene->l)
		return (L);
	else if (!ft_strcmp(array[0], "sp"))
		return (SP);
	else if (!ft_strcmp(array[0], "pl"))
		return (PL);
	else if (!ft_strcmp(array[0], "cy"))
		return (CY);
	else
		return (-1);
}

static bool	get_element(char **array, t_scene *scene)
{
	bool	flag;
	int		name;

	flag = true;
	name = find_element_name(array, scene);
	if (name == -1)
		flag = false;
	else if (name == -2)
		flag = true;
	else if (name == A && !get_el(A, scene, &array[1]))
		flag = false;
	else if (name == C && !get_el(C, scene, &array[1]))
		flag = false;
	else if (name == L && !get_el(L, scene, &array[1]))
		flag = false;
	else if (name == SP && !get_obj(SP, scene, new_sp(&array[1])))
		flag = false;
	else if (name == PL && !get_obj(PL, scene, new_pl(&array[1])))
		flag = false;
	else if (name == CY && !get_obj(CY, scene, new_cy(&array[1])))
		flag = false;
	free_array(array);
	if (flag == false)
		free_scene(scene);
	return (flag);
}

t_scene	*get_scene(int fd)
{
	t_scene	*scene;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->a = NULL;
	scene->c = NULL;
	scene->l = NULL;
	scene->obj = NULL;
	scene->mlx.ref = NULL;
	scene->mlx.win = NULL;
	scene->mlx.img.reference = NULL;
	while (line)
	{
		if (!get_element(ft_split_pop_back(line, " \t\n"), scene))
			return (free_element(line, scene));
		free(line);
		line = get_next_line(fd);
	}
	return (scene);
}
