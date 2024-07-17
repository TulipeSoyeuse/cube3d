/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_setter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:10:32 by romain            #+#    #+#             */
/*   Updated: 2024/07/17 14:12:59 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_plane(t_params *p, char c)
{
	if (c == 'N' || c == 'S')
	{
		p->plane.x = 0;
		p->plane.y = FOV;
	}
	else if (c == 'E' || c == 'W')
	{
		p->plane.x = FOV;
		p->plane.y = 0;
	}
	return (1);
}

int	set_dir(t_params *p, char c)
{
	if (c == 'N')
	{
		p->p_dir.x = -1;
		p->p_dir.y = 0;
	}
	else if (c == 'S')
	{
		p->p_dir.x = 1;
		p->p_dir.y = 0;
	}
	else if (c == 'E')
	{
		p->p_dir.x = 0;
		p->p_dir.y = -1;
	}
	else if (c == 'W')
	{
		p->p_dir.x = 0;
		p->p_dir.y = 1;
	}
	else
		return (0);
	return (set_plane(p, c));
}

void	set_player_position(t_params *p)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (p->map[i])
	{
		line = p->map[i];
		j = 0;
		while (line[j])
		{
			if (set_dir(p, line[j]))
			{
				p->map[i][j] = '0';
				p->p_pos.x = i;
				p->p_pos.y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	set_info(t_params *p)
{
	char	*s;
	int		len;
	char	*exp;

	exp = "pos : %f - %f";
	len = snprintf(NULL, 0, exp, p->p_pos.x, p->p_pos.y);
	s = malloc(len + 1);
	snprintf(s, len + 1, exp, p->p_pos.x, p->p_pos.y);
	mlx_string_put(p->w.mlx, p->w.mlx_win, 0, 0, 0xFFFFFF, s);
	free(s);
}

double	get_angle(t_vector a, t_vector b)
{
	double	denominator;

	denominator = sqrtl(a.x * a.x + a.y * a.y) * sqrtl(b.x * b.x + b.y * b.y);
	return (acos((a.x * b.x + a.y * b.y) / denominator));
}
