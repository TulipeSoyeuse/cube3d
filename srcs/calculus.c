/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:01:06 by romain            #+#    #+#             */
/*   Updated: 2024/04/20 19:20:55 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	is_hit(t_params *p, t_calc_values *cv)
{
	// printf("map:%f, %f\n", cv->map.x, cv->map.y);
	if (cv->sideDist.x < cv->sideDist.y)
	{
		cv->sideDist.x += cv->deltaDist.x;
		cv->map.x += cv->step.x;
		cv->side = False;
	}
	else
	{
		cv->sideDist.y += cv->deltaDist.y;
		cv->map.y += cv->step.y;
		cv->side = True;
	}
	if (p->map[(int)cv->map.x][(int)cv->map.y] == 1)
	{
		printf("hit on wall %d, %d\n", (int)cv->map.x, (int)cv->map.y);
		cv->hit = True;
	}
}

void	calc_side_dist(t_params *p, t_calc_values *cv)
{
	cv->map.x = (int)p->p_pos.x;
	cv->map.y = (int)p->p_pos.y;
	if (cv->rayDir.x < 0)
	{
		cv->step.x = -1;
		cv->sideDist.x = (p->p_pos.x - cv->map.x) * cv->deltaDist.x;
	}
	else
	{
		cv->step.x = 1;
		cv->sideDist.x = (cv->map.x + 1.0 - p->p_pos.x) * cv->deltaDist.x;
	}
	if (cv->rayDir.y < 0)
	{
		cv->step.y = -1;
		cv->sideDist.y = (p->p_pos.y - cv->map.y) * cv->deltaDist.y;
	}
	else
	{
		cv->step.y = 1;
		cv->sideDist.y = (cv->map.y + 1.0 - p->p_pos.y) * cv->deltaDist.y;
	}
}

t_vector	dist(t_params *p, double camX)
{
	t_vector	rayDir;
	t_vector	deltaDist;

	rayDir.x = p->p_dir.x + p->plane.x * camX;
	rayDir.y = p->p_dir.y + p->plane.y * camX;
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

int	get_perpwalldist(t_calc_values cv)
{
	if (cv.side == False)
		return (cv.sideDist.x - cv.deltaDist.x);
	else
		return (cv.sideDist.y - cv.deltaDist.y);
}

void	draw_ver_line(int line_nbr, int start, int end, t_img img)
{
	char	*dst;

	printf("writing wal, pxl up:%d to %d\n", start, end);
	while (start < end)
	{
		dst = img.addr + (start++ * img.line_length + line_nbr
				* (img.bits_per_pixel / 8));
		*(unsigned int *)dst = COLOR_RED;
	}
}

void	reset_img_color(t_img img)
{
	int		x;
	int		y;
	char	*dst;

	x = 0;
	y = 0;
	while (y < SWIDTH)
	{
		while (x < SHEIGHT)
		{
			dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel
						/ 8));
			*(unsigned int *)dst = 0;
			x++;
		}
		y++;
	}
}
