/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:16:42 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/11/20 18:29:12 by rgomes-c         ###   ########.fr       */
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
typedef struct s_matrix						t_matrix;
typedef struct s_raytrace					t_raytrace;
typedef struct s_closest					t_closest;
typedef struct s_object						t_object;
typedef struct s_inter						t_inter;

struct s_scene
{
	t_amb_light	*a;
	t_camera	*c;
	t_light		*l;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	t_object	*obj;
};

struct s_object
{
	int				type;
	void			*data;
	struct s_object	*next;
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

struct s_matrix
{
	t_coord	x;
	t_coord	y;
	t_coord	z;
};

struct s_closest
{
	bool		hit;
	int			type;
	void		*obj;
	t_coord		*pos;
	t_rgb		*color;
	double		t;
	double		x;
};

struct s_inter
{
	double	v1;
	double	v2;
};

struct s_raytrace
{
	t_coord		ray_origin;
	t_coord		ray_canvas;
	t_closest	closest;
};

enum e_objects
{
	SPHERE = 1,
	PLANE = 2,
	CYLINDER = 3
};

// ----------------------------- FUNCTIONS ---------------------------------- //

//utils.c
void		free_array(char **array);
void		debug(t_scene *scene);
t_coord		rotate_camera(t_coord orientation_vector, t_matrix rotation_matrix);
t_matrix	create_rotation_matrix(t_coord *ori);
t_coord		rotate_vector(t_coord vector, t_coord rotation);

#endif
