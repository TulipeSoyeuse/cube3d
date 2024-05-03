/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:45:46 by romain            #+#    #+#             */
/*   Updated: 2024/05/03 14:35:27 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_plane(t_params *p, char c)
{
	if (c == 'N' || c == 'S')
	{
		p->plane.x = FOV;
		p->plane.y = 0;
	}
	else if (c == 'E' || c == 'W')
	{
		p->plane.x = 0;
		p->plane.y = FOV;
	}
	return (1);
}

int	set_dir(t_params *p, char c)
{
	if (c == 'N')
	{
		p->p_dir.x = 0;
		p->p_dir.y = -1;
	}
	else if (c == 'S')
	{
		p->p_dir.x = 0;
		p->p_dir.y = 1;
	}
	else if (c == 'E')
	{
		p->p_dir.x = 1;
		p->p_dir.y = 0;
	}
	else if (c == 'W')
	{
		p->p_dir.x = -1;
		p->p_dir.y = 0;
	}
	else
		return (0);
	return (set_plane(p, c));
}

void	set_player_position(t_params *p)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (p->map[i])
	{
		line = p->map[i];
		j = 0;
		while (line[j])
		{
			if (set_dir(p, line[j]))
			{
				p->map[i][j] = '0';
				p->p_pos.x = i;
				p->p_pos.y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	set_info(t_params *p)
{
	char	*s;
	int		len;
	char	*exp;

	exp = "pos : %f - %f";
	len = snprintf(NULL, 0, exp, p->p_pos.x, p->p_pos.y);
	s = malloc(len + 1);
	snprintf(s, len + 1, exp, p->p_pos.x, p->p_pos.y);
	mlx_string_put(p->w.mlx, p->w.mlx_win, 0, 0, 0xFFFFFF, s);
	free(s);
}

void	run(t_params *p)
{
	display_params(p);
	p->w.cur_img = get_new_image(p);
	p->w.cache_img = get_new_image(p);
	calc_image(p);
	set_info(p);
	mlx_put_image_to_window(p->w.mlx, p->w.mlx_win, p->w.cur_img.img, 0, 0);
	loop(p);
}

t_img	get_new_image(t_params *p)
{
	t_img	image;

	image.img = mlx_new_image(p->w.mlx, SWIDTH, SHEIGHT);
	if (!image.img)
		cube_exit(p);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
			&image.line_length, &image.endian);
	if (!image.addr)
		error(p);
	return (image);
}

double	get_angle(t_vector a, t_vector b)
{
	double	denominator;

	denominator = sqrtl(a.x * a.x + a.y * a.y) * sqrtl(b.x * b.x + b.y * b.y);
	return (acos((a.x * b.x + a.y * b.y) / denominator));
}
void	second_part(t_calc_values *c, double angle)
{
	if (angle <= 3 * M_PI_2)
	{
		if (c->side == False)
			c->wall_ori = NO;
		else
			c->wall_ori = EA;
	}
	else
	{
		if (c->side == False)
			c->wall_ori = SO;
		else
			c->wall_ori = EA;
	}
}

void	define_ori(t_calc_values *c)
{
	double	angle;

	angle = atan2(c->rayDir.y, c->rayDir.x) + M_PI;
	if (angle <= M_PI_2)
	{
		if (c->side == False)
			c->wall_ori = SO;
		else
			c->wall_ori = WE;
	}
	else if (angle <= 2 * M_PI_2)
	{
		if (c->side == False)
			c->wall_ori = NO;
		else
			c->wall_ori = WE;
	}
	else
		second_part(c, angle);
}

void	calc_image(t_params *p)
{
	t_calc_values	c;
	int				x;

	reset_img_color(p, p->w.cur_img);
	x = -1;
	while (++x < SWIDTH)
	{
		dist(p, &c, 2 * x / (double)SWIDTH - 1);
		calc_side_dist(p, &c);
		while (!is_hit(p, &c))
			;
		get_perpwalldist(&c);
		draw_ver_line(&c, p, x);
	}
}
