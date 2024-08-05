/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:31:39 by romain            #+#    #+#             */
/*   Updated: 2024/08/05 13:38:32 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_left_exterior_wall(char **m)
{
	int	i;
	int	j;

	i = -1;
	while (m[++i])
	{
		j = 0;
		while (1)
		{
			if (!m[i][j] || m[i][j] == '0')
				return (1);
			if (m[i][j] == '1')
			{
				printf("left check -> line:%d char:%d\n", i, j);
				break ;
			}
			j++;
		}
	}
	return (0);
}

int	check_right_exterior_wall(char **m)
{
	int	i;
	int	j;

	i = -1;
	while (m[++i])
	{
		j = ft_strlen(m[i]) - 1;
		while (1)
		{
			if (!m[i][j] || m[i][j] == '0')
				return (1);
			if (m[i][j] == '1')
			{
				printf("right check -> line:%d char:%d\n", i, j);
				break ;
			}
			j--;
		}
	}
	return (0);
}

int	check_down_exterior_wall(char **m)
{
	int	i;
	int	j;
	int	map_len;

	map_len = -1;
	j = -1;
	while (m[++map_len])
		;
	i = map_len - 1;
	while (m[i][++j])
	{
		i = map_len - 1;
		while (1)
		{
			if (i == 0 || m[i][j] == '0')
				return (1);
			if (m[i][j] == '1')
			{
				printf("down check -> line:%d char:%d\n", i, j);
				break ;
			}
			i--;
		}
	}
	return (0);
}

int	check_up_exterior_wall(char **m)
{
	int	i;
	int	j;
	int	map_len;

	map_len = -1;
	j = -1;
	while (m[++map_len])
		;
	i = 0;
	while (m[i][++j])
	{
		i = 0;
		while (1)
		{
			if (i == map_len - 1 || m[i][j] == '0')
				return (1);
			if (m[i][j] == '1')
			{
				printf("up check -> line:%d char:%d\n", i, j);
				break ;
			}
			i++;
		}
	}
	return (0);
}

int	first_last_line_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0')
			return (1);
		i++;
	}
	return (0);
}

int	check_zero_map(char **m, int i, int j)
{
	if ((int)ft_strlen(m[i - 1]) < j || (int)ft_strlen(m[i + 1]) < j)
		return (1);
	if ((m[i - 1][j] == '0' || m[i - 1][j] == '1' || m[i - 1][j] == 'N' ||
		m[i - 1][j] == 'S' || m[i - 1][j] == 'W' || m[i - 1][j] == 'E') &&
		(m[i + 1][j] == '0' || m[i + 1][j] == '1' || m[i + 1][j] == 'N' ||
		m[i + 1][j] == 'S' || m[i + 1][j] == 'W' || m[i + 1][j] == 'E') &&
		(m[i][j - 1] == '0' || m[i][j - 1] == '1' || m[i][j - 1] == 'N' ||
		m[i][j - 1] == 'S' || m[i][j - 1] == 'W' || m[i][j - 1] == 'E') &&
		(m[i][j + 1] == '0' || m[i][j + 1] == '1' || m[i][j + 1] == 'N' ||
		m[i][j + 1] == 'S' || m[i][j + 1] == 'W' || m[i][j + 1] == 'E'))
		return (0);
	return (1);
}

int	check_map(char **m)
{
	int	i;
	int	j;

	if (check_left_exterior_wall(m) || check_right_exterior_wall(m)
		|| check_down_exterior_wall(m) || check_up_exterior_wall(m))
		return (1);
	i = 1;
	while (m[i + 1])
	{
		j = 1;
		while (m[i][j + 1])
		{
			if (m[i][j] == '0' && check_zero_map(m, i, j))
			{
				printf("return: %d %d", i, j);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
