/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:10:32 by romain            #+#    #+#             */
/*   Updated: 2024/04/19 12:39:26 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_map_env(int fd, char *line, t_params *p)
{
	char	**map;

	map = malloc(sizeof(char *) * 2);
	if (!map)
		map_error(*p, 1, line);
	map[0] = line;
	map[1] = NULL;
	line = get_next_line(fd);
	while (line)
	{
		map = add_line(map, line);
		if (!map)
			map_error(*p, 1, line);
		line = get_next_line(fd);
	}
	p->map = map;
}

void	read_map(int fd, t_params *p)
{
	char		*line;
	t_type_def	ti;

	while (1)
	{
		line = get_next_line(fd);
		if (is_empty(line))
		{
			free(line);
			continue ;
		}
		if (is_line_map(line))
		{
			set_map_env(fd, line, p);
			return ;
		}
		ti = get_identifier(line);
		if (!ti)
			map_error(*p, 1, line);
		set_identifier_handler(ti, line, p);
		free(line);
	}
}

void	display_params(t_params *p)
{
	int	i;

	printf("f_color:%x\n", p->f_color);
	printf("c_color:%x\n", p->c_color);
	printf("\nno_texture:%p\n", p->no_texture);
	printf("so_texture:%p\n", p->so_texture);
	printf("ea_texture:%p\n", p->ea_texture);
	printf("we_texture:%p\n", p->we_texture);
	printf("\nmap:\n");
	i = 0;
	while (p->map[i])
		printf("%s\n", p->map[i++]);
	printf("\nmlx_ptr:%p\n", p->w.mlx);
	printf("mlx_win:%p\n", p->w.mlx_win);
	printf("mlx_img1:%p\n", p->w.cur_img.img);
	printf("mlx_img2:%p\n", p->w.cache_img.img);
}

void	get_map(t_params *p, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		map_error(*p, 0);
	read_map(fd, p);
	// if (check_map(p->map))
	// 	map_error(*p, 0);
	display_params(p);
	close(fd);
}
