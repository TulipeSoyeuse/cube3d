/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:41:30 by romain            #+#    #+#             */
/*   Updated: 2024/04/29 17:13:35 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_event(t_params *p)
{
	cube_exit(p);
	return (0);
}

void	display_new_image(t_params *p)
{
	t_img	buf;

	buf = p->w.cur_img;
	p->w.cur_img = p->w.cache_img;
	p->w.cache_img = buf;
	reset_img_color(p, p->w.cur_img);
	calc_image(p, p->w.cur_img);
	mlx_put_image_to_window(p->w.mlx, p->w.mlx_win, p->w.cur_img.img, 0, 0);
}

void	move_down(t_params *p)
{
	if (p->map[(int)(p->p_pos.x + p->p_dir.x
			* MOVESPEED)][(int)p->p_pos.y] != '1')
		p->p_pos.x -= p->p_dir.x * MOVESPEED;
	if (p->map[(int)p->p_pos.x][(int)(p->p_pos.y + p->p_dir.y
			* MOVESPEED)] != '1')
		p->p_pos.y -= p->p_dir.y * MOVESPEED;
}

void	move_up(t_params *p)
{
	if (p->map[(int)(p->p_pos.x + p->p_dir.x
			* MOVESPEED)][(int)p->p_pos.y] != '1')
		p->p_pos.x += p->p_dir.x * MOVESPEED;
	if (p->map[(int)p->p_pos.x][(int)(p->p_pos.y + p->p_dir.y
			* MOVESPEED)] != '1')
		p->p_pos.y += p->p_dir.y * MOVESPEED;
}

void	move_left(t_params *p)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = p->p_dir.x;
	p->p_dir.x = p->p_dir.x * cos(-ROTATION_SPEED) - p->p_dir.y
		* sin(-ROTATION_SPEED);
	p->p_dir.y = oldDirX * sin(-ROTATION_SPEED) + p->p_dir.y
		* cos(-ROTATION_SPEED);
	oldPlaneX = p->plane.x;
	p->plane.x = p->plane.x * cos(-ROTATION_SPEED) - p->plane.y
		* sin(-ROTATION_SPEED);
	p->plane.y = oldPlaneX * sin(-ROTATION_SPEED) + p->plane.y
		* cos(-ROTATION_SPEED);
}

void	move_right(t_params *p)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = p->p_dir.x;
	p->p_dir.x = p->p_dir.x * cos(ROTATION_SPEED) - p->p_dir.y
		* sin(ROTATION_SPEED);
	p->p_dir.y = oldDirX * sin(ROTATION_SPEED) + p->p_dir.y
		* cos(ROTATION_SPEED);
	oldPlaneX = p->plane.x;
	p->plane.x = p->plane.x * cos(ROTATION_SPEED) - p->plane.y
		* sin(ROTATION_SPEED);
	p->plane.y = oldPlaneX * sin(ROTATION_SPEED) + p->plane.y
		* cos(ROTATION_SPEED);
}

int	key_hook(int button, t_params *p)
{
	// printf("button pressed: %d\n", button);
	if (button == EVENT_CLOSE_BTN || button == KEY_ESC)
		cube_exit(p);
	else if (button == KEY_UP)
		move_up(p);
	else if (button == KEY_DOWN)
		move_down(p);
	else if (button == KEY_LEFT)
		move_left(p);
	else if (button == KEY_RIGHT)
		move_right(p);
	display_params(p);
	display_new_image(p);
	return (0);
}
