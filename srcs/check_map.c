/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:31:39 by romain            #+#    #+#             */
/*   Updated: 2024/07/23 15:41:56 by romain           ###   ########.fr       */
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

int	check_map(char **m)
{
	if (check_left_exterior_wall(m))
		return (1);
	if (check_right_exterior_wall(m))
		return (1);
	if (check_down_exterior_wall(m))
		return (1);
	if (check_up_exterior_wall(m))
		return (1);
	(void)m;
	return (0);
}
