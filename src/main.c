/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qwerty <qwerty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:23:41 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/19 19:04:43 by qwerty           ###   ########.fr       */
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
	t_coord		*camera_origin;
	t_vector	o_vp;
	t_coord		d;
};

// Assumindo que distancia da camara ao plano de projecao é 1 unidade;
// tan(alpha) = cateto oposto sobre o cateto adjacente;
// para calcular a largura é nada mais do que uma regra de 3 simples;
t_viewport	get_viewport_dimensions(int fov)
{
	t_viewport	viewport;
	double		alpha;
	double		rad;

	rad = fov * (M_PI / 180);
	alpha = rad / 2;
	viewport.d = 1.0;
	viewport.vh = 2 * tan(alpha) * viewport.d;
	viewport.vw = viewport.vh * C_W / C_H;
	return (viewport);
}

// Para calcular cada coordenada do viewport fazemos tambem uma regra 3 simples;
t_coord	canvas_to_viewport(double cx, double cy, t_viewport view)
{
	t_coord	vp;

	vp.x = cx * view.vw / C_W;
	vp.y = cy * view.vh / C_H;
	vp.z = view.d;
	return (vp);
}

t_rgb	get_color_light(t_sphere *closest_sp, t_rgb *color, t_vector *p, t_vector *n, t_scene *scene)
{
	t_rgb	tmp_color;
	double	tmp_cl;

	if (!closest_sp)
		return (*color);
	tmp_cl = compute_lighting(scene, p, n);
	tmp_color.r = closest_sp->color->r * tmp_cl;
	tmp_color.g = closest_sp->color->g * tmp_cl;
	tmp_color.b = closest_sp->color->b * tmp_cl;
	return (tmp_color);
}

void	sphere_intersection(t_scene *scene, t_vector *d, t_image *img, int x, int y)
{
	t_rgb		color;
	double		closest_t;
	t_sphere	*temp;
	double		*inter;
	double		util;
	t_vector	p;
	t_vector	n;
	t_sphere	*closest_sp;

	closest_t = __DBL_MAX__;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 0;
	temp = scene->sp;
	closest_sp = NULL;
	while (temp)
	{
		inter = ray_intersect_sphere(scene, temp, d);
		if (inter)
		{
			if (inter[0] < inter[1])
				util = inter[0];
			else
				util = inter[1];
			if (util < closest_t)
			{
				closest_t = inter[0];
				closest_sp = temp;
			}
			free(inter);
		}
		temp = temp->next;
	}
	p = find_p(d, scene->c->pos, closest_t);
	if (closest_sp)
	{
		n = subtract((t_coord *)&p, closest_sp->pos);
		n = vec_normalize(&n);
	}
	turn_pixel_to_color(&img->pixels[(x + C_W / 2) * 4 + img->line_size * (y + C_H / 2)], get_color_light(closest_sp, &color, &p, &n, scene));
}

void	start_ray(t_scene *scene, void *mlx, void *mlx_window)
{
	t_rt		rt;
	int			x;
	int			y;
	t_image		img;
	t_viewport	vp;
	t_coord		c_on_vp;
	t_vector	vector_o_vp;

	if (!scene)
		return ;
	(void)rt;
	vp = get_viewport_dimensions(scene->c->fov);
	rt.bg_color.r = 255;
	rt.bg_color.g = 0;
	rt.bg_color.b = 0;
	img = ft_new_image(mlx, C_W, C_H);
	y = -C_H / 2 - 1;
	while (++y < C_H / 2)
	{
		x = -C_W / 2 - 1;
		while (++x < C_W / 2)
		{
			c_on_vp = canvas_to_viewport(x, y, vp);
			vector_o_vp = subtract(&c_on_vp, scene->c->pos);
			sphere_intersection(scene, &vector_o_vp, &img, x, y);
		}
	}
	mlx_put_image_to_window(mlx, mlx_window, img.reference, 0, 0);
}

int	ft_xbutton(t_scene *scene)
{
	free_scene(scene);
	exit (0);
}

void	ft_esc(int key, t_scene *scene)
{
	if (key == KEY_ESC)
	{
		free_scene(scene);
		exit (0);	
	}
}

int	main(int ac, char **av)
{
	t_scene	*scene;
	void	*mlx;
	void	*mlx_win;

	scene = NULL;
	parse(ac, av, &scene);
	(void)mlx;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, C_W, C_H, "Test");
	mlx_hook(mlx_win, X_WINBUTTON, 1L << 3, &ft_xbutton, &scene);
	//scene->esc = 0;
	//mlx_loop_hook(window.mlx, ft_work, &window);
	start_ray(scene, mlx, mlx_win);
	mlx_loop(mlx);
	free_scene(scene);
	return (0);
}
