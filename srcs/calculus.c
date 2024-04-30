/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:01:06 by romain            #+#    #+#             */
/*   Updated: 2024/04/29 20:36:52 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_hit(t_params *p, t_calc_values *cv)
{
	if (cv->sideDist.x < cv->sideDist.y)
	{
		cv->sideDist.x += cv->deltaDist.x;
		cv->mapX += cv->stepX;
		cv->side = False;
	}
	else
	{
		cv->sideDist.y += cv->deltaDist.y;
		cv->mapY += cv->stepY;
		cv->side = True;
	}
	if (p->map[cv->mapX][cv->mapY] > '0' && p->map[cv->mapX][cv->mapY] <= '9')
	{
		define_ori(cv);
		return (1);
	}
	return (0);
}

void	calc_side_dist(t_params *p, t_calc_values *cv)
{
	cv->mapX = (int)p->p_pos.x;
	cv->mapY = (int)p->p_pos.y;
	if (cv->rayDir.x < 0)
	{
		cv->stepX = -1;
		cv->sideDist.x = (p->p_pos.x - cv->mapX) * cv->deltaDist.x;
	}
	else
	{
		cv->stepX = 1;
		cv->sideDist.x = (cv->mapX + 1.0 - p->p_pos.x) * cv->deltaDist.x;
	}
	if (cv->rayDir.y < 0)
	{
		cv->stepY = -1;
		cv->sideDist.y = (p->p_pos.y - cv->mapY) * cv->deltaDist.y;
	}
	else
	{
		cv->stepY = 1;
		cv->sideDist.y = (cv->mapY + 1.0 - p->p_pos.y) * cv->deltaDist.y;
	}
}

void	dist(t_params *p, t_calc_values *c, double camX)
{
	c->rayDir.x = p->p_dir.x + p->plane.x * camX;
	c->rayDir.y = p->p_dir.y + p->plane.y * camX;
	if (c->rayDir.x == 0)
		c->deltaDist.x = 1e30;
	else
		c->deltaDist.x = fabs(1 / c->rayDir.x);
	if (c->rayDir.y == 0)
		c->deltaDist.y = 1e30;
	else
		c->deltaDist.y = fabs(1 / c->rayDir.y);
}

double	get_perpwalldist(t_calc_values cv)
{
	if (cv.side == False)
		return (cv.sideDist.x - cv.deltaDist.x);
	else
		return (cv.sideDist.y - cv.deltaDist.y);
}

void	draw_ver_line(int col_nbr, int start, int end, t_img img, int color)
{
	char	*dst;

	while (start < end)
	{
		dst = img.addr + (start++ * img.line_length + col_nbr
				* (img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	reset_img_color(t_params *p, t_img img)
{
	int		x;
	int		y;
	char	*dst;

	y = 0;
	while (y < SHEIGHT)
	{
		x = 0;
		while (x < SWIDTH)
		{
			dst = img.addr + (y * img.line_length + x++ * (img.bits_per_pixel
						/ 8));
			if (y < SHEIGHT / 2)
				*(unsigned int *)dst = p->c_color;
			else
				*(unsigned int *)dst = p->f_color;
		}
		y++;
	}
}
