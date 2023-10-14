/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:23:41 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/13 16:58:09 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <string.h>

typedef struct s_viewport	t_viewport;
typedef struct s_rt			t_rt;

struct s_viewport
{
	double				vw;
	double				vh;
	double				d;
};

struct s_rt
{
	t_viewport	vp;
	t_rgb		bg_color;
	t_vector	*o;
	t_vector	v;
	t_vector	d;
};

t_viewport	get_viewport(int fov)
{
	t_viewport	viewport;
	double		fov_rad;

	fov_rad = fov * (M_PI / 180.0);
	viewport.vh = 2 * tan(fov_rad / 2);
	viewport.vw = viewport.vh * C_W / C_H;
	viewport.d = 1.0;
	return (viewport);
}

t_vector	canvas_to_viewport(double cx, double cy, t_viewport view)
{
	t_vector	vp;

	vp.x = cx * view.vw / C_W;
	vp.y = cy * view.vh / C_H;
	vp.z = view.d;
	return (vp);
}

t_vector	subtract(t_vector *vector1, t_vector *vector2)
{
	t_vector	result;

	result.x = vector1->x - vector2->x;
	result.y = vector1->y - vector2->y;
	result.z = vector1->z - vector2->z;
	return (result);
}

double	dot(t_vector *vector1, t_vector *vector2)
{
	return (vector1->x * vector2->x + vector1->y * vector2->y
		+ vector1->z * vector2->z);
}

double	ray_intersect_shpere_util(double a, double b, double disc)
{
	double	t1;
	double	t2;

	t1 = (-b + sqrt(disc)) / (2 * a);
	t2 = (-b - sqrt(disc)) / (2 * a);
	if (t1 >= 0)
		return (t1);
	else if (t2 >= 0)
		return (t2);
	else
		return (-1);
}

double	ray_intersect_shpere(t_rt *rt, t_sphere *sphere)
{
	t_vector	co;
	double		b;
	double		c;
	double		disc;
	double		t1;
	// double		t2;

	co = subtract(rt->o, sphere->pos);
	b = 2 * dot(&co, &rt->d);
	c = dot(&co, &co) - ((sphere->d / 2) * (sphere->d / 2));
	disc = (b * b) - (4 * c);
	if (disc < 0)
		return (-1);
	t1 = (-b - sqrt(disc)) / 2;
	// t2 = (-b - sqrt(disc)) / 2;
	if (t1 > 0)
		return (1);
	// if (t2 >= 0)
	// 	return (t2);
	return (-1);
}

t_rgb	trace_ray(t_rt *rt, t_sphere *sphere, double t_min, double t_max)
{
	t_sphere	*temp;
	t_sphere	*closest_sphere;
	// double		closest_t;
	int			num_spheres;
	int			i;

	(void) t_max;
	(void) t_min;
	temp = sphere;
	num_spheres = 1;
	// closest_t = __DBL_MAX__;
	closest_sphere = NULL;
	i = -1;
	while (++i < num_spheres)
	{
		if (ray_intersect_shpere(rt, temp))
		{
			// closest_t = t;
			closest_sphere = temp;
		}
		temp = temp->next;
	}
	if (closest_sphere == NULL)
		return (rt->bg_color);
	return (*closest_sphere->color);
}

void	start_ray(t_scene *scene, void *mlx, void *mlx_window)
{
	t_rt	rt;
	int		x;
	int		y;
	t_image	img;

	rt.bg_color.r = 255;
	rt.bg_color.g = 0;
	rt.bg_color.b = 0;
	img = ft_new_image(mlx, C_W, C_H);
	rt.o = scene->c->pos;
	rt.vp = get_viewport(scene->c->fov);
	y = -1;
	while (++y < C_H)
	{
		x = -1;
		while (++x < C_W)
		{
			rt.v = canvas_to_viewport(x, y, rt.vp);
			rt.d = subtract(&rt.v, rt.o);
			turn_pixel_to_color(
				&img.pixels[x * 4 + img.line_size * y],
				trace_ray(&rt, scene->sp, 1, __DBL_MAX__));
		}
	}
	mlx_put_image_to_window(mlx, mlx_window, img.reference, 0, 0);
}

int	main(int ac, char **av)
{
	t_scene	*scene;
	void	*mlx;
	void	*mlx_win;

	scene = NULL;
	parse(ac, av, &scene);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, C_W, C_H, "Test");
	start_ray(scene, mlx, mlx_win);
	mlx_loop(mlx);
	return (0);
}
