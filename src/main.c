/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:23:41 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/17 15:21:05 by rgomes-c         ###   ########.fr       */
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

void	sphere_intersection(t_scene *scene, t_vector *d, t_image *img, int x, int y)
{
	t_rgb		color;
	double		closest_t;
	t_sphere	*temp;
	double		*inter;
	double		util;

	closest_t = __DBL_MAX__;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 0;
	temp = scene->sp;
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
				color = *temp->color;
			}
			free(inter);
		}
		temp = temp->next;
	}
	turn_pixel_to_color(&img->pixels[(x + C_W / 2) * 4 + img->line_size * (y + C_H / 2)], color);
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
