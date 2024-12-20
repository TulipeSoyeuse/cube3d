/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:10:32 by romain            #+#    #+#             */
/*   Updated: 2024/12/06 15:55:35 by rdupeux          ###   ########.fr       */
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

void	get_map(t_params *p, char *path)
{
	int		fd;
	size_t	len;

	len = ft_strlen(path);
	fd = open(path, O_RDONLY);
	if (fd == -1 || strcmp(&path[len - 4], ".cub"))
		error(p, "can't open file or wrong extension\n");
	read_map(fd, p);
	if (check_map(p->map))
		error(p, NULL);
	close(fd);
}

// void	display_params(t_params *p)
// {
// 	int	i;

// 	printf("f_color:%x\n", p->f_color);
// 	printf("c_color:%x\n", p->c_color);
// 	printf("\nno_texture:%p\n", p->no_texture.addr);
// 	printf("so_texture:%p\n", p->so_texture.addr);
// 	printf("ea_texture:%p\n", p->ea_texture.addr);
// 	printf("we_texture:%p\n", p->we_texture.addr);
// 	printf("\npos:%f %f\n", p->p_pos.x, p->p_pos.y);
// 	printf("dir:%f %f\n", p->p_dir.x, p->p_dir.y);
// 	printf("plane:%f %f\n", p->plane.x, p->plane.y);
// 	printf("perpendicular: %f\n", p->p_dir.x * p->plane.x + p->p_dir.y
// 		* p->plane.y);
// 	printf("\nmap:\n");
// 	i = 0;
// 	while (p->map[i])
// 		printf("%s\n", p->map[i++]);
// 	printf("\nmlx_ptr:%p\n", p->w.mlx);
// 	printf("mlx_win:%p\n", p->w.mlx_win);
// 	printf("mlx_img1:%p\n", p->w.cur_img.img);
// 	printf("mlx_img2:%p\n", p->w.cache_img.img);
// }
