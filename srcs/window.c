/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:20:32 by romain            #+#    #+#             */
/*   Updated: 2024/04/19 17:11:01 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cube_exit(t_params *p)
{
	cleanup(p);
	exit(EXIT_SUCCESS);
}

int	key_hook(int button, t_params *p)
{
	printf("button pressed: %d", button);
	if (button == EVENT_CLOSE_BTN || button == KEY_ESC)
		cube_exit(p);
	return (0);
}

void	loop(t_params *p)
{
	mlx_hook(p->w.mlx_win, EVENT_CLOSE_BTN, 0, &key_hook, p);
	mlx_hook(p->w.mlx_win, KEY_ESC, 0, &key_hook, p);
	mlx_loop(p->w.mlx);
}
