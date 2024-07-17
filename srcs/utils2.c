/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:25:17 by romain            #+#    #+#             */
/*   Updated: 2024/07/17 14:26:09 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**add_line(char **map, char *line)
{
	size_t	size_map;
	char	**new_map;

	size_map = 0;
	while (map[size_map])
		size_map++;
	new_map = malloc(sizeof(char *) * (size_map + 2));
	if (!new_map)
		return (map);
	size_map = 0;
	while (map[size_map])
	{
		new_map[size_map] = map[size_map];
		size_map++;
	}
	new_map[size_map] = line;
	new_map[size_map + 1] = NULL;
	free(map);
	return (new_map);
}
