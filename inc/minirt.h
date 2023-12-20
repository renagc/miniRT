/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gseco-lu <gseco-lu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:16:42 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/20 12:12:21 by gseco-lu         ###   ########.fr       */
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
#  define C_W 800
# endif
# ifndef C_H
#  define C_H 700
# endif

// ------------------------------ HOOKS ----------------------------------- //

# define KEY_PRESS		2
# define KEY_RELEASE	3
# define X_WINBUTTON	17
# define KEY_ESC		65307

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
typedef struct s_raytrace					t_raytrace;
typedef struct s_closest					t_closest;
typedef struct s_object						t_object;
typedef struct s_inter						t_inter;
typedef struct s_matrix						t_matrix;
typedef struct s_mlx						t_mlx;
typedef struct s_viewport					t_viewport;
typedef struct s_image						t_image;

struct s_mlx
{
	void	*ref;
	void	*win;
	t_image	img;
};

struct s_scene
{
	t_amb_light	*a;
	t_camera	*c;
	t_light		*l;
	t_object	*obj;
	t_mlx		mlx;
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
};

struct s_amb_light
{
	double	ratio;
	t_rgb	color;
};

struct s_camera
{
	t_coord			pos;
	t_coord			ori;
	unsigned char	fov;
};

struct s_light
{
	t_coord			pos;
	double			ratio;
};

struct s_sphere
{
	t_coord			pos;
	double			d;
	t_rgb			color;
};

struct s_plane
{
	t_coord			pos;
	t_coord			ori;
	t_rgb			color;
};

struct s_cylinder
{
	t_coord				pos;
	t_coord				ori;
	double				d;
	double				h;
	t_rgb				color;
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

struct s_matrix
{
	double	m[4][4];
};

struct s_viewport
{
	double				vw;
	double				vh;
	double				d;
};

enum e_scene
{
	C = 1,
	L = 2,
	A = 3,
	SP = 4,
	PL = 5,
	CY = 6
};

// ----------------------------- FUNCTIONS ---------------------------------- //

//utils.c
void		free_array(char **array);
void		debug(t_scene *scene);
t_coord		rotate_camera(t_coord orientation_vector, t_matrix rotation_matrix);
t_matrix	create_rotation_matrix(t_coord *ori);
t_coord		rotate_vector(t_coord vector, t_coord rotation);

//transform.c
t_coord		transform_point(t_coord point, double matrix[4][4]);
t_coord		transform_direction(t_coord direction, double matrix[4][4]);


//inter.c
bool		intersect_ray_sphere(double t_min, double t_max, \
			t_raytrace *rt, t_sphere *sp);
bool		intersect_ray_plane(double t_min, double t_max, \
			t_raytrace *rt, t_plane *plane);
bool		get_closest_obj(t_raytrace *rt, double t, int type, void *obj);
int			intersect_ray_cylinder(double t_min, double t_max, \
			t_raytrace *rt, t_cylinder *cy);

//inter_cy_utils_1.c
t_matrix	new_matrix(t_coord v1, t_coord v2, t_coord v3);
t_matrix	matrix_cy(t_cylinder *cy);
bool		cy_quadratic_f(t_coord *local_ray_dir, \
			t_coord *local_ray_ori, t_cylinder *cy, double *t);
t_coord		*check_cap(double *t, t_coord *local_ray_origin, \
			t_coord *local_ray_dir, t_cylinder *cy);

//inter_cy_utils_2.c
void		calc_t(t_raytrace *rt, t_cylinder *cy, \
			t_coord *local_ray, double *t);
void		calc_z(t_raytrace *rt, t_cylinder *cy, \
			double *t, t_coord *local_ray);

//raytrace.c
double		compute_light(t_raytrace *rt, t_coord *n, t_scene *scene);
t_rgb		*trace_ray(t_raytrace *rt, t_scene *scene);
void		start_ray(t_scene *scene, t_raytrace *rt);
void		closest_intersection(double t_min, double t_max, t_raytrace *rt, t_scene *scene);

//hooks.c
int			ft_xbutton(t_scene *scene);
int			ft_escbutton(int key, t_scene *scene);

//main.c
t_coord		canvas_to_viewport(double cx, double cy, t_viewport view);
t_viewport	get_viewport_dimensions(int fov);
t_coord		get_cylinder_normal(t_coord *point, \
			t_cylinder *cylinder);
t_scene *free_element(char *line, t_scene *scene);



#endif
