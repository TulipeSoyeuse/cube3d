/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:41:30 by romain            #+#    #+#             */
/*   Updated: 2024/12/06 15:06:18 by rdupeux          ###   ########.fr       */
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
	calc_image(p);
	mlx_put_image_to_window(p->w.mlx, p->w.mlx_win, p->w.cur_img.img, 0, 0);
}

void	look_right(t_params *p)
{
	double	olddirx;
	double	oldplanex;

	olddirx = p->p_dir.x;
	p->p_dir.x = p->p_dir.x * cos(-M_PI / 8) - p->p_dir.y * sin(-M_PI / 8);
	p->p_dir.y = olddirx * sin(-M_PI / 8) + p->p_dir.y * cos(-M_PI / 8);
	oldplanex = p->plane.x;
	p->plane.x = p->plane.x * cos(-M_PI / 8) - p->plane.y * sin(-M_PI / 8);
	p->plane.y = oldplanex * sin(-M_PI / 8) + p->plane.y * cos(-M_PI / 8);
}

void	look_left(t_params *p)
{
	double	olddirx;
	double	oldplanex;

	olddirx = p->p_dir.x;
	p->p_dir.x = p->p_dir.x * cos(M_PI / 8) - p->p_dir.y * sin(M_PI / 8);
	p->p_dir.y = olddirx * sin(M_PI / 8) + p->p_dir.y * cos(M_PI / 8);
	oldplanex = p->plane.x;
	p->plane.x = p->plane.x * cos(M_PI / 8) - p->plane.y * sin(M_PI / 8);
	p->plane.y = oldplanex * sin(M_PI / 8) + p->plane.y * cos(M_PI / 8);
}

int	key_hook(int button, t_params *p)
{
	if (button == EVENT_CLOSE_BTN || button == KEY_ESC)
		cube_exit(p);
	else if (button == KEY_UP)
		move_up(p);
	else if (button == KEY_DOWN)
		move_down(p);
	else if (p->start == 'S' || p->start == 'W')
		key_hook2(button, p);
	else if (button == LEFT_ARROW)
		look_left(p);
	else if (button == RIGHT_ARROW)
		look_right(p);
	else if (button == KEY_LEFT)
		move_left(p);
	else if (button == KEY_RIGHT)
		move_right(p);
	display_new_image(p);
	return (0);
}
