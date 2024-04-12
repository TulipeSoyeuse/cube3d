/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:50:14 by romain            #+#    #+#             */
/*   Updated: 2024/04/12 13:48:13 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_space(int c)
{
	if (c == '\t' || c == ' ' || c == '\v' || c == '\r')
		return (1);
	return (0);
}

int	is_empty(char *s)
{
	if (*s == 0)
		return (1);
	return (0);
}

int	is_line_map(char *line)
{
	int	pos;

	pos = 0;
	while (line)
	{
		if (*line != '1' && *line != '0' && !is_space(*line))
		{
			if (!pos && (*line == 'W' || *line == 'S' || *line == 'N'
					|| *line == 'E'))
				pos = 1;
			else
				return (0);
		}
		line++;
	}
	return (1);
}

int	is_path(char *path)
{
	int	code;

	code = open(path, O_RDONLY);
	if (code >= 0)
	{
		close(code);
		return (1);
	}
	return (0);
}

int	ft_atoin(const char *s, int n)
{
	char	*buf;
	int		res;

	buf = malloc(n + 1);
	if (!buf)
		return (-1);
	ft_strlcpy(buf, s, n);
	res = ft_atoi(buf);
	free(buf);
	return (res);
}

char	**add_line(char **map, char *line)
{
	size_t	size_map;
	char	**new_map;

	size_map = 0;
	while (map[size_map])
		size_map++;
	new_map = malloc(sizeof(char *) * (size_map + 2));
	if (!new_map)
		return (NULL);
	size_map = 0;
	while (map[size_map])
	{
		new_map = map;
		size_map++;
	}
	new_map[size_map] = line;
	new_map[size_map + 1] = NULL;
	return (new_map);
}
