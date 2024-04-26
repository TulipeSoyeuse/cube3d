/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:45:46 by romain            #+#    #+#             */
/*   Updated: 2024/04/26 12:43:19 by romain           ###   ########.fr       */
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
		switch (p->map[c.mapX][c.mapY])
		{
		case 1:
			color = COLOR_RED;
			break ; // red
		case 2:
			color = COLOR_GREEN;
			break ; // green
		case 3:
			color = COLOR_BLUE;
			break ; // blue
		case 4:
			color = 0;
			break ; // white
		default:
			color = COLOR_YELLOW;
			break ; // yellow
		}
		if (c.side == 1)
		{
			color = color / 2;
		}
		draw_ver_line(x, drawStart, drawEnd, img, color);
	}
}
