/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:45:46 by romain            #+#    #+#             */
/*   Updated: 2024/12/06 15:10:45 by rdupeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	run(t_params *p)
{
	display_params(p);
	p->w.cur_img = get_new_image(p);
	p->w.cache_img = get_new_image(p);
	calc_image(p);
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
		error(p, "error creating image\n");
	return (image);
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

	angle = atan2(c->raydir.y, c->raydir.x) + M_PI;
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
