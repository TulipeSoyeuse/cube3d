/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:19:17 by romain            #+#    #+#             */
/*   Updated: 2024/12/03 12:20:37 by romain           ###   ########.fr       */
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
				// printf("left check -> line:%d char:%d\n", i, j);
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
				// printf("right check -> line:%d char:%d\n", i, j);
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
				// printf("down check -> line:%d char:%d\n", i, j);
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
				// printf("up check -> line:%d char:%d\n", i, j);
				break ;
			}
			i++;
		}
	}
	return (0);
}

// int	get_point_value(char **m, int i, int j)
// {
// 	if (m[i][j] == '1')
// 		return (WALL);
// 	if (m[i][j] == '0' || m[i][j] == 'N' || m[i][j] == 'W' || m[i][j] == 'S'
// 		|| m[i][j] == 'E')
// 		return (GAME_SPACE);
// 	if (m[i][j] == ' ')
// 		return (EMPTY);
// 	else
// 		return (1);
// }

// int	set_starting_point(int *sp, char **m)
// {
// 	sp[0] = 0;
// 	sp[1] = 0;
// 	while (sp[1] < (int)ft_strlen(m[sp[0]]))
// 	{
// 		if (m[sp[0]][sp[1]] == ' ')
// 			sp[1]++;
// 		else if (m[sp[0]][sp[1]] == '0')
// 			return (1);
// 		else
// 			return (0);
// 	}
// 	return (1);
// }

// int	check_map2(char **m)
// {
// 	int	sp[2];

// 	set_starting_point(sp, m);
// 	while (m[sp[0] + 1])
// 		;
// 	return (0);
// }
