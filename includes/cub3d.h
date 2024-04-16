/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:52:13 by romain            #+#    #+#             */
/*   Updated: 2024/04/13 12:25:27 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H
# include "../libft/libft.h"
# include "../minignl/includes/minignl.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>

// SCREEN
# define SWIDTH 640
# define SHEIGHT 480

// KEY
# define EVENT_CLOSE_BTN 17
# define KEY_ESC 65307

typedef enum e_type_def
{
	NONE,
	NO,
	SO,
	WE,
	EA,
	F,
	C
}				t_type_def;

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_img
{
	void		*img;
	char		*addr;

	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_window
{
	void		*mlx;
	void		*mlx_win;
	t_img		cur_img;
	t_img		cache_img;
}				t_window;

typedef struct s_params
{
	t_window	w;
	t_vector	p_pos;
	t_vector	p_dir;
	t_vector	plane;
	void		*no_texture;
	void		*so_texture;
	void		*we_texture;
	void		*ea_texture;
	char		**map;
	int			f_color;
	int			c_color;
}				t_params;

t_img			get_new_image(t_window *w);
void			mlx_exit(t_window *w);
void			calc_image(t_window *w, t_params p);

// MAP PARSING
void			get_map(t_params *p, char *path);
char			**add_line(char **map, char *line);
t_type_def		get_identifier(const char *s);
void			set_identifier_handler(t_type_def, char *, t_params *);

// UTILS
int				is_space(int c);
int				is_empty(char *s);
int				is_line_map(char *line);
int				ft_atoin(const char *s, int n);
int				is_path(char *path);

// EXIT
void			map_error(t_params p, int argc, ...);
void			cleanup(t_params *p);
void			error(t_params *p);

// DEBUG

#endif
