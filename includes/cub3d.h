/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:52:13 by romain            #+#    #+#             */
/*   Updated: 2024/04/20 17:41:43 by romain           ###   ########.fr       */
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
# define SWIDTH 900
# define SHEIGHT 600

// KEY
# define EVENT_CLOSE_BTN 1869819968
# define KEY_ESC 65307

# define COLOR_BLUE 0x003C43
# define COLOR_RED 0xED4545
# define COLOR_WHITE 0xFFFFFF
# define COLOR_YELLOW 0xFCC100
# define COLOR_GREEN 0x5DAF00

typedef enum e_bool
{
	False,
	True
}				t_bool;

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

typedef struct s_calc_values
{
	t_vector	map;
	t_vector	deltaDist;
	t_vector	rayDir;
	t_vector	sideDist;
	t_vector	step;
	t_bool		side;
	t_bool		hit;
}				t_calc_values;

t_img			get_new_image(t_params *p);
void			calc_image(t_params *p, t_img img);

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
void			cube_exit(t_params *p);

// CALCULUS
void			is_hit(t_params *p, t_calc_values *cv);
void			calc_side_dist(t_params *p, t_calc_values *cv);
t_vector		dist(t_params *p, double camX);
void			draw_ver_line(int line, int start, int end, t_img img);
int				get_perpwalldist(t_calc_values cv);
void			set_player_position(t_params *p);

// RUNNING
void			run(t_params *p);
void			loop(t_params *p);
void			reset_img_color(t_img img);

#endif
