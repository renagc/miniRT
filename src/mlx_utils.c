/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qwerty <qwerty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:01:46 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/12/19 14:45:09 by qwerty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	turn_pixel_to_color(char *pixel, t_rgb *color)
{
	if (!color)
	{
		pixel[0] = 0;
		pixel[1] = 0;
		pixel[2] = 0;
		pixel[3] = 0;
		return ;
	}
	pixel[0] = color->b;
	pixel[1] = color->g;
	pixel[2] = color->r;
	pixel[3] = 0;
}

t_image	ft_new_image(void *mlx, int width, int height)
{
	t_image	img;

	img.reference = mlx_new_image(mlx, width, height);
	img.width = width;
	img.height = height;
	img.pixels = mlx_get_data_addr(img.reference, &img.bits_per_pixel \
		, &img.line_size, &img.endian);
	return (img);
}
