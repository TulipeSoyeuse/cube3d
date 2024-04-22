/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:02:35 by romain            #+#    #+#             */
/*   Updated: 2024/04/20 18:00:34 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_params	init(char *path)
{
	int			fd;
	t_params	p;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	p.c_color = 0;
	p.f_color = 0;
	p.w.mlx = NULL;
	p.w.mlx_win = NULL;
	p.ea_texture = NULL;
	p.no_texture = NULL;
	p.so_texture = NULL;
	p.we_texture = NULL;
	p.w.cache_img.img = NULL;
	p.w.cur_img.img = NULL;
	p.w.mlx = mlx_init();
	if (!p.w.mlx)
		error(&p);
	p.w.mlx_win = mlx_new_window(p.w.mlx, SHEIGHT, SWIDTH, "Cube3D");
	if (!p.w.mlx_win)
		error(&p);
	get_map(&p, path);
	return (p);
}

int	main(int ac, char **av)
{
	t_params	p;

	if (ac != 2)
		return (EXIT_FAILURE);
	p = init(av[1]);
	set_player_position(&p);
	printf("pos:%f %f\n", p.p_pos.x, p.p_pos.y);
	p.plane.x = 0;
	p.plane.y = 0.66;
	run(&p);
	cleanup(&p);
	return (0);
}
