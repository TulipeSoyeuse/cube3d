/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:01:06 by romain            #+#    #+#             */
/*   Updated: 2024/05/01 21:16:54 by romain           ###   ########.fr       */
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

void	get_perpwalldist(t_calc_values *cv)
{
	if (cv->side == False)
		cv->perpwalldist = cv->sideDist.x - cv->deltaDist.x;
	else
		cv->perpwalldist = cv->sideDist.y - cv->deltaDist.y;
}

t_img	get_texture(t_params *p, t_calc_values *c)
{
	if (c->wall_ori == NO)
		return (p->no_texture);
	if (c->wall_ori == SO)
		return (p->so_texture);
	if (c->wall_ori == EA)
		return (p->ea_texture);
	return (p->we_texture);
}

void	putline(t_params *p, t_calc_values *c, int col_nbr)
{
	char	*dst;
	int		texX;
	double	step;
	double	texPos;
	int		texY;
	void	*color;
	t_img	texture;
	double	wallX;

	texture = get_texture(p, c);
	if (c->side == 0)
		wallX = p->p_pos.y + c->perpwalldist * c->rayDir.y;
	else
		wallX = p->p_pos.x + c->perpwalldist * c->rayDir.x;
	wallX -= floor((wallX));
	texX = wallX * (double)texture.effective_widht;
	if (c->side == 0 && c->rayDir.x > 0)
		texX = texture.effective_widht - texX - 1;
	if (c->side == 0 && c->rayDir.y < 0)
		texX = texture.effective_widht - texX - 1;
	step = 1.0 * texture.effective_height / c->lineheight;
	texPos = (c->start - SHEIGHT / 2 + c->lineheight / 2) * step;
	while (c->start < c->end)
	{
		texY = (int)texPos & (texture.line_length - 1);
		texPos += step;
		color = texture.addr + ((texture.line_length * texY) + texX
				* (p->w.cur_img.bits_per_pixel / 8));
		dst = p->w.cur_img.addr + (c->start++ * p->w.cur_img.line_length
				+ col_nbr * (p->w.cur_img.bits_per_pixel / 8));
		*(unsigned int *)dst = *(unsigned int *)color;
	}
}

void	draw_ver_line(t_calc_values *c, t_params *p, int col_nbr)
{
	c->lineheight = (int)(SHEIGHT / c->perpwalldist);
	c->start = -c->lineheight / 2 + SHEIGHT / 2;
	if (c->start < 0)
		c->start = 0;
	c->end = c->lineheight / 2 + SHEIGHT / 2;
	if (c->end >= SHEIGHT)
		c->end = SHEIGHT - 1;
	putline(p, c, col_nbr);
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
