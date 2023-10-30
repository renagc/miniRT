/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:16:42 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/30 17:23:19 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// ------------------------------ HEADERS ----------------------------------- //

# include "../lib/minilibx/mlx.h"
# include "../lib/libft/libft.h"
# include "mlx_utils.h"
# include "parse.h"
# include "math_calc.h"
# include <stdio.h>
# include <math.h>

// ------------------------------- MACROS ----------------------------------- //

# ifndef C_W
#  define C_W 500
# endif
# ifndef C_H
#  define C_H 500
# endif

// ------------------------------ STRUCTS ----------------------------------- //

typedef struct s_coord						t_coord;
typedef struct s_rgb						t_rgb;
typedef struct s_amb_light					t_amb_light;
typedef struct s_camera						t_camera;
typedef struct s_light						t_light;
typedef struct s_sphere						t_sphere;
typedef struct s_plane						t_plane;
typedef struct s_cylinder					t_cylinder;
typedef struct s_scene						t_scene;
typedef struct s_vector						t_vector;

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

struct s_coord
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
	unsigned char	a;
};

struct s_amb_light
{
	double	ratio;
	t_rgb	*color;
};

struct s_camera
{
	t_coord			*pos;
	t_coord			*ori;
	unsigned char	fov;
};

struct s_light
{
	t_coord			*pos;
	double			ratio;
};

struct s_sphere
{
	t_coord			*pos;
	double			d;
	t_rgb			*color;
	struct s_sphere	*next;
};

struct s_plane
{
	t_coord			*pos;
	t_coord			*ori;
	t_rgb			*color;
	struct s_plane	*next;
};

struct s_cylinder
{
	t_coord				*pos;
	t_coord				*ori;
	double				d;
	double				h;
	t_rgb				*color;
	struct s_cylinder	*next;
};

// ----------------------------- FUNCTIONS ---------------------------------- //

//utils.c
void	free_array(char **array);
void	debug(t_scene *scene);

#endif
