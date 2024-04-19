/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:45:46 by romain            #+#    #+#             */
/*   Updated: 2024/04/19 12:38:14 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	run(t_params *p)
{
	p->w.cur_img = get_new_image(p);
	p->w.cache_img = get_new_image(p);
	calc_image(p, p->w.cur_img);
	mlx_put_image_to_window(p->w.mlx, p->w.mlx_win, p->w.cur_img.img, 0, 0);
	loop(p);
}

t_img	get_new_image(t_params *p)
{
	t_img	image;

	image.img = mlx_new_image(p->w.mlx, SHEIGHT, SWIDTH);
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
	int				x;
	t_calc_values	cv;
	int				lineHeight;
	double			perpWallDist;
	int				drawStart;
	int				drawEnd;

	x = -1;
	reset_img_color(img);
	while (x++ < SWIDTH)
	{
		cv.deltaDist = dist(p, 2 * x / (double)SWIDTH - 1);
		calc_side_dist(p, &cv);
		while (cv.hit == False)
			is_hit(p, &cv);
		perpWallDist = get_perpwalldist(cv);
		lineHeight = (int)(SHEIGHT / perpWallDist);
		drawStart = -lineHeight / 2 + SHEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + SHEIGHT / 2;
		if (drawEnd >= SHEIGHT)
			drawEnd = SHEIGHT - 1;
		draw_ver_line(x, drawStart, drawEnd, img);
	}
}
