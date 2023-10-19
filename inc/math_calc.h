/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_calc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qwerty <qwerty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:01:54 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/19 17:34:20 by qwerty           ###   ########.fr       */
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
double		vec_length(t_vector *vec);
t_vector	vec_normalize(t_vector *vec);
double		product(t_vector *vec1, t_vector *vec2);
t_vector	find_p(t_vector *vec1, t_coord *coord1, double x);

//sphere.c
double		*ray_intersect_sphere(t_scene *scene, t_sphere *sphere, \
			t_vector *d);

#endif