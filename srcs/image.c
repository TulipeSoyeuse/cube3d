/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:45:46 by romain            #+#    #+#             */
/*   Updated: 2024/04/30 12:25:31 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_plane(t_params *p, char c)
{
	if (c == 'N' || c == 'S')
	{
		printf("PING %c\n", c);
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
	printf("setting player pos\n");
	while (p->map[i])
	{
		line = p->map[i];
		j = 0;
		while (line[j])
		{
			if (set_dir(p, line[j]))
			{
				p->p_pos.x = i;
				p->p_pos.y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	run(t_params *p)
{
	display_params(p);
	p->w.cur_img = get_new_image(p);
	p->w.cache_img = get_new_image(p);
	calc_image(p, p->w.cur_img);
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

void	calc_image(t_params *p, t_img img)
{
	t_calc_values	c;
	double			perpWallDist;
	int				lineHeight;
	int				drawStart;
	int				drawEnd;
	int				x;
	int				color;

	reset_img_color(p, img);
	x = -1;
	while (++x < SWIDTH)
	{
		dist(p, &c, 2 * x / (double)SWIDTH - 1);
		calc_side_dist(p, &c);
		while (!is_hit(p, &c))
			;
		perpWallDist = get_perpwalldist(c);
		lineHeight = (int)(SHEIGHT / perpWallDist);
		drawStart = -lineHeight / 2 + SHEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + SHEIGHT / 2;
		if (drawEnd >= SHEIGHT)
			drawEnd = SHEIGHT - 1;
		switch (c.wall_ori)
		{
		case NO:
			color = COLOR_BLUE;
			break ;
		case SO:
			color = COLOR_GREEN;
			break ;
		case EA:
			color = COLOR_RED;
			break ;
		case WE:
			color = COLOR_YELLOW;
			break ;
		default:
			color = COLOR_WHITE;
			break ;
		}
		draw_ver_line(x, drawStart, drawEnd, img, color);
	}
}
