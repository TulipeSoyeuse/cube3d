/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:45:46 by romain            #+#    #+#             */
/*   Updated: 2024/04/03 18:13:52 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	dist(t_params p, double camX)
{
	t_vector	rayDir;
	t_vector	deltaDist;

	rayDir.x = p.p_dir.x + p.plane.x * camX;
	rayDir.y = p.p_dir.y + p.plane.y * camX;
	if (!rayDir.x)
		deltaDist.x = 1e30;
	else
		deltaDist.x = fabs(1 / rayDir.x);
	if (!rayDir.y)
		deltaDist.y = 1e30;
	else
		deltaDist.y = fabs(1 / rayDir.y);
	return (deltaDist);
}

t_img	get_new_image(t_window *window)
{
	t_img	image;

	image.img = mlx_new_image(window->mlx, sHeight, sWidth);
	if (!image.img)
		mlx_exit(window);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
			&image.line_length, &image.endian);
	if (!image.addr)
		mlx_exit(window);
	return (image);
}

void	calc_image(t_window *w, t_params p)
{
	int			x;
	int			hit;
	int			side;
	t_vector	map;
	t_vector	deltaDist;
	t_vector	rayDir;
	t_vector	sideDist;
	t_vector	step;

	x = -1;
	while (x++ < sWidth)
	{
		deltaDist = dist(p, 2 * x / (double)sWidth - 1);
		map.x = (int)p.p_pos.x;
		map.y = (int)p.p_pos.y;
		if (rayDir.x < 0)
		{
			step.x = -1;
			sideDist.x = (p.p_pos.x - map.x) * deltaDist.x;
		}
		else
		{
			step.x = 1;
			sideDist.x = (map.x + 1.0 - p.p_pos.x) * deltaDist.x;
		}
		if (rayDir.y < 0)
		{
			step.y = -1;
			sideDist.y = (p.p_pos.y - map.y) * deltaDist.y;
		}
		else
		{
			step.y = 1;
			sideDist.y = (map.y + 1.0 - p.p_pos.y) * deltaDist.y;
		}
		while (hit == 0)
		{
			if (sideDist.x < sideDist.y)
			{
				sideDist.x += deltaDist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				sideDist.y += deltaDist.y;
				map.y += step.y;
				side = 1;
			}
			if (worldMap[map.x][map.y] > 0)
				hit = 1;
		}
	}
}
