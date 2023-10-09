/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:16:42 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/07 13:07:56 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// ------------------------------ HEADERS ----------------------------------- //
# include "../lib/minilibx/mlx.h"
# include "../lib/libft/libft.h"
# include "parse.h"
# include <stdio.h>

// ------------------------------ STRUCTS ----------------------------------- //

typedef struct s_vector						t_vector;
typedef struct s_rgb						t_rgb;
typedef struct s_amb_light					t_amb_light;
typedef struct s_camera						t_camera;
typedef struct s_light						t_light;
typedef struct s_sphere						t_sphere;
typedef struct s_plane						t_plane;
typedef struct s_cylinder					t_cylinder;
typedef struct s_scene						t_scene;

struct s_scene
{
	t_amb_light	*a;
	t_camera	*c;
	t_light		*l;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
};

struct s_vector
{
	double	x;
	double	y;
	double	z;
};

struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
};

struct s_amb_light
{
	double	ratio;
	t_rgb	*color;
};

struct s_camera
{
	t_vector		*pos;
	t_vector		*ori;
	unsigned char	fov;
};

struct s_light
{
	t_vector		*pos;
	double			ratio;
};

struct s_sphere
{
	t_vector		*pos;
	double			d;
	t_rgb			*color;
	struct s_sphere	*next;
};

struct s_plane
{
	t_vector		*pos;
	t_vector		*ori;
	t_rgb			*color;
	struct s_plane	*next;
};

struct s_cylinder
{
	t_vector			*pos;
	t_vector			*ori;
	double				d;
	double				h;
	t_rgb				*color;
	struct s_cylinder	*next;
};

// ----------------------------- FUNCTIONS ---------------------------------- //

//utils.c
t_scene	*scene(void);
void	free_array(char **array);

// ------------------------------- MACROS ----------------------------------- //

#endif