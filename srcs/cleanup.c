/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:05:05 by romain            #+#    #+#             */
/*   Updated: 2024/04/13 12:30:51 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_cleanup(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		// printf("%p - %d - %s\n", map[i], i, map[i]);
		free(map[i++]);
	}
	free(map);
}

void	cleanup(t_params *p)
{
	if (p->ea_texture)
		mlx_destroy_image(p->w.mlx, p->ea_texture);
	if (p->no_texture)
		mlx_destroy_image(p->w.mlx, p->no_texture);
	if (p->so_texture)
		mlx_destroy_image(p->w.mlx, p->so_texture);
	if (p->we_texture)
		mlx_destroy_image(p->w.mlx, p->we_texture);
	if (p->w.cache_img.img)
		mlx_destroy_image(p->w.mlx, p->w.cache_img.img);
	if (p->w.cur_img.img)
		mlx_destroy_image(p->w.mlx, p->w.cur_img.img);
	if (p->w.mlx_win)
		mlx_destroy_window(p->w.mlx, p->w.mlx_win);
	if (p->w.mlx)
		mlx_destroy_display(p->w.mlx);
	map_cleanup(p->map);
}

void	error(t_params *p)
{
	cleanup(p);
	exit(EXIT_FAILURE);
}

void	map_error(t_params p, int argc, ...)
{
	va_list	a_lst;
	char	*arg;

	cleanup(&p);
	va_start(a_lst, argc);
	while (argc--)
	{
		arg = va_arg(a_lst, char *);
		if (arg)
			free(arg);
	}
	va_end(a_lst);
	write(1, "MAP ERROR\n", 10);
	exit(1);
}
