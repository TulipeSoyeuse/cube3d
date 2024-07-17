/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculus2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:21:53 by romain            #+#    #+#             */
/*   Updated: 2024/07/17 14:32:10 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_hit(t_params *p, t_calc_values *cv)
{
	if (cv->sidedist.x < cv->sidedist.y)
	{
		cv->sidedist.x += cv->deltadist.x;
		cv->mapx += cv->stepx;
		cv->side = False;
	}
	else
	{
		cv->sidedist.y += cv->deltadist.y;
		cv->mapy += cv->stepy;
		cv->side = True;
	}
	if (p->map[cv->mapx][cv->mapy] > '0' && p->map[cv->mapx][cv->mapy] <= '9')
	{
		define_ori(cv);
		return (1);
	}
	return (0);
}

void	calc_side_dist(t_params *p, t_calc_values *cv)
{
	cv->mapx = (int)p->p_pos.x;
	cv->mapy = (int)p->p_pos.y;
	if (cv->raydir.x < 0)
	{
		cv->stepx = -1;
		cv->sidedist.x = (p->p_pos.x - cv->mapx) * cv->deltadist.x;
	}
	else
	{
		cv->stepx = 1;
		cv->sidedist.x = (cv->mapx + 1.0 - p->p_pos.x) * cv->deltadist.x;
	}
	if (cv->raydir.y < 0)
	{
		cv->stepy = -1;
		cv->sidedist.y = (p->p_pos.y - cv->mapy) * cv->deltadist.y;
	}
	else
	{
		cv->stepy = 1;
		cv->sidedist.y = (cv->mapy + 1.0 - p->p_pos.y) * cv->deltadist.y;
	}
}

void	dist(t_params *p, t_calc_values *c, double camX)
{
	c->raydir.x = p->p_dir.x + p->plane.x * camX;
	c->raydir.y = p->p_dir.y + p->plane.y * camX;
	if (c->raydir.x == 0)
		c->deltadist.x = 1e30;
	else
		c->deltadist.x = fabs(1 / c->raydir.x);
	if (c->raydir.y == 0)
		c->deltadist.y = 1e30;
	else
		c->deltadist.y = fabs(1 / c->raydir.y);
}

void	get_perpwalldist(t_calc_values *cv)
{
	if (cv->side == False)
		cv->perpwalldist = cv->sidedist.x - cv->deltadist.x;
	else
		cv->perpwalldist = cv->sidedist.y - cv->deltadist.y;
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
