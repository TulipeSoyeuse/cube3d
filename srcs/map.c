/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:10:32 by romain            #+#    #+#             */
/*   Updated: 2024/04/02 16:49:43 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_params	get_map(t_window w, char *path)
{
	t_params	p;
	int			x;

	p.map = malloc(sizeof(char *) * 5);
	x = -1;
	p.map[0] = "111111";
	p.map[1] = "100101";
	p.map[2] = "101001";
	p.map[3] = "1100N1";
	p.map[4] = "111111";
	p.NO_texture = mlx_xpm_file_to_image(w.mlx, "assets/colorstone.xpm", 60,
			60);
	p.SO_texture = mlx_xpm_file_to_image(w.mlx, "assets/colorstone.xpm", 60,
			60);
	p.WE_texture = mlx_xpm_file_to_image(w.mlx, "assets/colorstone.xpm", 60,
			60);
	p.EA_texture = mlx_xpm_file_to_image(w.mlx, "assets/colorstone.xpm", 60,
			60);
}
