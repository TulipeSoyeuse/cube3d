/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:10:32 by romain            #+#    #+#             */
/*   Updated: 2024/04/12 13:29:52 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_map_env(int fd, char *line, t_params *p)
{
	char	**map;

	map = malloc(sizeof(char *) * 2);
	map[0] = line;
	map[1] = NULL;
	while (is_line_map(line))
	{
		line = get_next_line(fd);
		map = add_line(map, line);
		if (!map)
			map_error(*p, 1, line);
	}
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
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		map_error(*p, 0);
	close(fd);
	read_map(fd, p);
}
