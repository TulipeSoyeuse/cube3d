/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:20:32 by romain            #+#    #+#             */
/*   Updated: 2024/04/02 15:55:18 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_exit(t_window *mlx)
{
	if (mlx->cur_img.img)
		mlx_destroy_image(mlx->mlx, mlx->cur_img.img);
	if (mlx->cache_img.img)
		mlx_destroy_image(mlx->mlx, mlx->cache_img.img);
	if (mlx->mlx_win)
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	exit(EXIT_SUCCESS);
}

void	loop(t_window mlx, int v)
{
	// mlx_mouse_hook(mlx.mlx_win, &mouse_hook_julia, &mlx);
	// mlx_key_hook(mlx.mlx_win, &key_hook_julia, &mlx);
	mlx_hook(mlx.mlx_win, EVENT_CLOSE_BTN, 0, mlx_exit, &mlx);
	mlx_hook(mlx.mlx_win, KEY_ESC, 0, mlx_exit, &mlx);
	mlx_loop(mlx.mlx);
}

t_window	init(void)
{
	t_window	w;

	w.cur_img.img = NULL;
	w.cache_img.img = NULL;
	w.mlx = NULL;
	w.mlx_win = NULL;
	w.mlx = mlx_init();
	if (!w.mlx)
		mlx_exit(&w);
	w.mlx_win = mlx_new_window(w.mlx, sWidth, sHeight, "Cube3D");
	if (!w.mlx_win)
		mlx_exit(&w);
	w.cur_img = get_new_image(&w);
	w.cache_img = get_new_image(&w);
}
