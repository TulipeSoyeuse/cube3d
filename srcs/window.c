/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:20:32 by romain            #+#    #+#             */
/*   Updated: 2024/04/19 17:51:02 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cube_exit(t_params *p)
{
	cleanup(p);
	exit(EXIT_SUCCESS);
}

int	close_event(t_params *p)
{
	cube_exit(p);
	return (0);
}

int	key_hook(int button, t_params *p)
{
	printf("button pressed: %d\n", button);
	if (button == EVENT_CLOSE_BTN || button == KEY_ESC)
		cube_exit(p);
	return (0);
}

void	loop(t_params *p)
{
	printf("loop\n");
	mlx_key_hook(p->w.mlx_win, &key_hook, p);
	mlx_hook(p->w.mlx_win, 17, 0, &close_event, p);
	mlx_loop(p->w.mlx);
}
