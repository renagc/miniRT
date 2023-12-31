/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_calc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:01:54 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/30 12:27:13 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_CALC_H
# define MATH_CALC_H

// ------------------------------ HEADERS ----------------------------------- //

# include <limits.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <string.h>
# include <stdbool.h>

// ------------------------------ STRUCTS ----------------------------------- //

typedef struct s_coord						t_coord;
typedef struct s_vector						t_vector;
typedef struct s_scene						t_scene;
typedef struct s_sphere						t_sphere;

// ----------------------------- FUNCTIONS ---------------------------------- //

//vector.c
t_vector	subtract(t_coord *coord1, t_coord *coord2);
double		vec_length(t_coord *vec);
void		vec_normalize(t_coord *vec);
double		product(t_coord *coord1, t_coord *coord2);
t_coord		add_const(t_coord *coord1, t_coord *coord2, double constant);
t_coord		subtract_const(t_coord *coord1, t_coord *coord2, double constant);
t_rgb		*multiply_color(t_rgb *color, double multiply);

//sphere.c
double		*ray_intersect_sphere(t_scene *scene, t_sphere *sphere, \
			t_vector *d);

#endif