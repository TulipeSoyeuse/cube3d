/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:01:06 by romain            #+#    #+#             */
/*   Updated: 2024/07/17 14:30:14 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	putline(t_params *p, t_calc_values *c, int col_nbr)
{
	t_putline_val	v;

	v.texture = get_texture(p, c);
	if (c->side == 0)
		v.wallx = p->p_pos.y + c->perpwalldist * c->raydir.y;
	else
		v.wallx = p->p_pos.x + c->perpwalldist * c->raydir.x;
	v.wallx -= floor((v.wallx));
	v.texx = v.wallx * (double)v.texture.effective_widht;
	if (c->side == 0 && c->raydir.x > 0)
		v.texx = v.texture.effective_widht - v.texx - 1;
	if (c->side == 0 && c->raydir.y < 0)
		v.texx = v.texture.effective_widht - v.texx - 1;
	v.step = 1.0 * v.texture.effective_height / c->lineheight;
	v.texpos = (c->start - SHEIGHT / 2 + c->lineheight / 2) * v.step;
	while (c->start < c->end)
	{
		v.texy = (int)v.texpos & (v.texture.line_length - 1);
		v.texpos += v.step;
		v.color = v.texture.addr + ((v.texture.line_length * v.texy) + v.texx
				* (p->w.cur_img.bits_per_pixel / 8));
		v.dst = p->w.cur_img.addr + (c->start++ * p->w.cur_img.line_length
				+ col_nbr * (p->w.cur_img.bits_per_pixel / 8));
		*(unsigned int *)v.dst = *(unsigned int *)v.color;
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
