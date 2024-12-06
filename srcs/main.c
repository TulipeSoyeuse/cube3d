/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:02:35 by romain            #+#    #+#             */
/*   Updated: 2024/12/06 14:36:23 by rdupeux          ###   ########.fr       */
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
	p.ea_texture.img = NULL;
	p.no_texture.img = NULL;
	p.so_texture.img = NULL;
	p.we_texture.img = NULL;
	p.w.cache_img.img = NULL;
	p.w.cur_img.img = NULL;
	p.map = NULL;
	p.w.mlx = mlx_init();
	if (!p.w.mlx)
		error(&p, "error initializing mlx\n");
	p.w.mlx_win = mlx_new_window(p.w.mlx, SWIDTH, SHEIGHT, "Cube3D");
	if (!p.w.mlx_win)
		error(&p, "error creating window\n");
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
	run(&p);
	cleanup(&p);
	return (0);
}
