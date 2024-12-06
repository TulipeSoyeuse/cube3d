/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:01:16 by romain            #+#    #+#             */
/*   Updated: 2024/12/06 15:03:09 by rdupeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_down(t_params *p)
{
	if (p->map[(int)(p->p_pos.x - p->p_dir.x
			* MOVESPEED)][(int)p->p_pos.y] != '1')
		p->p_pos.x -= p->p_dir.x * MOVESPEED;
	else
		return ;
	if (p->map[(int)p->p_pos.x][(int)(p->p_pos.y - p->p_dir.y
		* MOVESPEED)] != '1')
		p->p_pos.y -= p->p_dir.y * MOVESPEED;
}

void	move_up(t_params *p)
{
	if (p->map[(int)(p->p_pos.x + p->p_dir.x
			* MOVESPEED)][(int)p->p_pos.y] != '1')
		p->p_pos.x += p->p_dir.x * MOVESPEED;
	else
		return ;
	if (p->map[(int)p->p_pos.x][(int)(p->p_pos.y + p->p_dir.y
		* MOVESPEED)] != '1')
		p->p_pos.y += p->p_dir.y * MOVESPEED;
}

void	move_left(t_params *p)
{
	if (p->map[(int)(p->p_pos.x - p->p_dir.y
			* MOVESPEED)][(int)p->p_pos.y] != '1')
		p->p_pos.x += -p->p_dir.y * MOVESPEED;
	else
		return ;
	if (p->map[(int)p->p_pos.x][(int)(p->p_pos.y + p->p_dir.x
		* MOVESPEED)] != '1')
		p->p_pos.y += p->p_dir.x * MOVESPEED;
}

void	move_right(t_params *p)
{
	if (p->map[(int)(p->p_pos.x + p->p_dir.y
			* MOVESPEED)][(int)p->p_pos.y] != '1')
		p->p_pos.x += p->p_dir.y * MOVESPEED;
	else
		return ;
	if (p->map[(int)p->p_pos.x][(int)(p->p_pos.y - p->p_dir.x
		* MOVESPEED)] != '1')
		p->p_pos.y += -p->p_dir.x * MOVESPEED;
}
