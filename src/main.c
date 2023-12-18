/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:23:41 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/18 21:33:34 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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

	(void)view;
	vp.x = cx * view.vw / C_W;
	vp.y = cy * view.vh / C_H;
	vp.z = view.d;
	return (vp);
}

t_coord	get_cylinder_normal(t_coord *point, \
	t_cylinder *cylinder)
{
	t_coord	ctp;
	t_coord	n;
	t_coord	normal;
	double	pt;

	ctp = subtract_const(point, &cylinder->pos, 1);
	pt = product(&cylinder->ori, &ctp);
	n.x = (&cylinder->ori)->x * pt;
	n.y = (&cylinder->ori)->y * pt;
	n.z = (&cylinder->ori)->z * pt;
	normal = subtract_const(&ctp, &n, 1);
	vec_normalize(&normal);
	return (normal);
}

int	main(int ac, char **av)
{
	t_scene		*scene;
	t_raytrace	rt;

	scene = NULL;
	parse(ac, av, &scene);
	scene->mlx.ref = mlx_init();
	scene->mlx.win = mlx_new_window(scene->mlx.ref, C_W, C_H, "Test");
	debug(scene);
	start_ray(scene, &rt);
	mlx_hook(scene->mlx.win, X_WINBUTTON, 1L << 3, &ft_xbutton, &scene);
	mlx_hook(scene->mlx.win, KEY_PRESS, 1, ft_escbutton, &scene);
	mlx_hook(scene->mlx.win, KEY_RELEASE, 1, ft_escbutton, &scene);
	mlx_loop(scene->mlx.ref);
	return (0);
}
