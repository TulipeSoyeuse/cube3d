/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:25:22 by romain            #+#    #+#             */
/*   Updated: 2024/04/10 16:37:32 by romain           ###   ########.fr       */
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

t_type_def	get_identifier(const char *s)
{
	while (*s)
	{
		if (!is_space(*s))
		{
			if (!strncmp(s, "NO ", 5))
				return (NO);
			if (!strncmp(s, "SO ", 5))
				return (SO);
			if (!strncmp(s, "EA ", 5))
				return (EA);
			if (!strncmp(s, "WE ", 5))
				return (WE);
			if (!strncmp(s, "C ", 4))
				return (C);
			if (!strncmp(s, "F ", 4))
				return (F);
		}
		s++;
	}
	return (0);
}

void	set_identifier(t_type_def type, char *line, t_params *p)
{
	if (type == NO)
}
