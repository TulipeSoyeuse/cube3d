/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:52:13 by romain            #+#    #+#             */
/*   Updated: 2024/07/18 17:51:49 by romain           ###   ########.fr       */
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
# define SWIDTH 1200
# define SHEIGHT 800
# define TEXHEIGHT 64
# define TEXWIDHT 64
// KEY
# define EVENT_CLOSE_BTN 1869819968
# define KEY_ESC 65307
# define KEY_LEFT 113
# define KEY_UP 122
# define KEY_RIGHT 100
# define KEY_DOWN 115
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

# define MOVESPEED 0.5

# define COLOR_BLUE 0x003C43
# define COLOR_RED 0xED4545
# define COLOR_WHITE 0xFFFFFF
# define COLOR_YELLOW 0xFCC100
# define COLOR_GREEN 0x5DAF00

# define FOV 0.66

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

typedef enum e_bool
{
	False,
	True
}				t_bool;

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
	int			effective_height;
	int			effective_widht;
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
	t_img		no_texture;
	t_img		so_texture;
	t_img		we_texture;
	t_img		ea_texture;
	char		**map;
	int			f_color;
	int			c_color;
}				t_params;

typedef struct s_calc_values
{
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	int			start;
	int			end;
	double		perpwalldist;
	int			lineheight;
	t_vector	deltadist;
	t_vector	raydir;
	t_vector	sidedist;
	t_type_def	wall_ori;
	t_bool		side;

}				t_calc_values;

typedef struct s_putline_val
{
	char		*dst;
	int			texx;
	double		step;
	double		texpos;
	int			texy;
	void		*color;
	t_img		texture;
	double		wallx;
}				t_putline_val;

t_img			get_new_image(t_params *p);
void			calc_image(t_params *p);

// MAP PARSING
void			get_map(t_params *p, char *path);
char			**add_line(char **map, char *line);
t_type_def		get_identifier(const char *s);
void			set_identifier_handler(t_type_def t, char *c, t_params *p);

// UTILS
int				is_space(int c);
int				is_empty(char *s);
int				is_line_map(char *line);
int				ft_atoin(const char *s, int n);
int				is_path(char *path);
void			display_params(t_params *p);

// EXIT
void			map_error(t_params p, int argc, ...);
void			cleanup(t_params *p);
void			error(t_params *p);
void			cube_exit(t_params *p);
int				close_event(t_params *p);

// CALCULUS
int				is_hit(t_params *p, t_calc_values *cv);
void			calc_side_dist(t_params *p, t_calc_values *cv);
void			dist(t_params *p, t_calc_values *c, double camX);
void			draw_ver_line(t_calc_values *c, t_params *p, int col_nbr);
void			get_perpwalldist(t_calc_values *cv);
void			set_player_position(t_params *p);
void			define_ori(t_calc_values *c);
double			get_angle(t_vector a, t_vector b);
t_img			get_texture(t_params *p, t_calc_values *c);

// RUNNING
void			run(t_params *p);
void			loop(t_params *p);
void			reset_img_color(t_params *p, t_img img);

// HOOKS
int				key_hook(int button, t_params *p);

// CAMERA MOVE
void			move_down(t_params *p);
void			move_up(t_params *p);
void			move_left(t_params *p);
void			move_right(t_params *p);

// IMAGE SETTER
int				set_plane(t_params *p, char c);
int				set_dir(t_params *p, char c);
void			set_player_position(t_params *p);
void			set_info(t_params *p);
double			get_angle(t_vector a, t_vector b);
#endif
