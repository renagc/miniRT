/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:01:54 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/10/14 12:43:43 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

// ------------------------------ HEADERS ----------------------------------- //

# include <limits.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <string.h>
# include <stdbool.h>

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

// ----------------------------- FUNCTIONS ---------------------------------- //

//get_scene.c
t_scene			*get_scene(int fd);

//get_pl.c
int				get_pl(t_plane **pl_lst, char **array);

//get_cy.c
int				get_cy(t_cylinder **cy_lst, char **array);

//get_sp.c
int				get_sp(t_sphere **sp_lst, char **array);

//get_amb_light.c
t_amb_light		*get_amb_light(char **array);
t_light			*get_light(char **array);

//get_rgc.c
t_rgb			*get_rgb(char *str);

//get_camera.c
int				is_coord(t_coord *coord);
t_camera		*get_camera(char **array);

//get_coord.c
int				is_double(char *str);
t_coord		*get_coord(char *str);

//parse.c
void			parse(int ac, char **av, t_scene **scene);

// utils.c
char			**ft_split_pop_back(char *str, char *set);

//free_scene.c
void			free_scene(t_scene *scene);

#endif
