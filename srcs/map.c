/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:10:32 by romain            #+#    #+#             */
/*   Updated: 2024/04/10 16:35:45 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_error(t_params p, int argc, ...)
{
	va_list	a_lst;
	char	*arg;

	va_start(a_lst, argc);
	while (argc--)
	{
		arg = va_arg(a_lst, char *);
		if (arg)
			free(arg);
	}
	va_end(a_lst);
	write(1, "MAP ERROR", 10);
	exit(1);
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
		set_identifier(ti, line, p);
	}
}

t_params	get_map(t_window w, char *path)
{
	t_params	p;
	int			x;
	int			fd;

	p.ea_texture = NULL;
	p.no_texture = NULL;
	p.we_texture = NULL;
	p.so_texture = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		map_error(p, 0);
	read_map(fd, &p);
}
