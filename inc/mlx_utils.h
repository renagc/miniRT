/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 20:55:15 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/11/27 10:24:52 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

// ------------------------------ STRUCTS ----------------------------------- //

typedef struct s_image	t_image;
typedef struct s_rgb	t_rgb;

struct	s_image
{
	void		*reference;
	int			width;
	int			height;
	char		*pixels;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
};

// ----------------------------- FUNCTIONS ---------------------------------- //

void		turn_pixel_to_color(char *pixel, t_rgb *color);
t_image		ft_new_image(void *mlx, int width, int height);

#endif