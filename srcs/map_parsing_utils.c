/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:25:22 by romain            #+#    #+#             */
/*   Updated: 2024/12/11 12:39:57 by rdupeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_hex(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

t_type_def	get_identifier(const char *s)
{
	while (*s)
	{
		if (!is_space(*s))
		{
			if (!strncmp(s, "NO ", 3))
				return (NO);
			if (!strncmp(s, "SO ", 3))
				return (SO);
			if (!strncmp(s, "EA ", 3))
				return (EA);
			if (!strncmp(s, "WE ", 3))
				return (WE);
			if (!strncmp(s, "C ", 2))
				return (C);
			if (!strncmp(s, "F ", 2))
				return (F);
		}
		s++;
	}
	return (0);
}

void	set_color(int *color, const char *line, t_params *p)
{
	int	offset;
	int	r;
	int	g;
	int	b;

	while (!is_space(*line))
		line++;
	line++;
	offset = ft_strchr(line, ',') - line;
	r = ft_atoin(line, offset + 1);
	line += offset + 1;
	offset = ft_strchr(line, ',') - line;
	g = ft_atoin(line, offset + 1);
	line += offset + 1;
	b = ft_atoi(line);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error(p, "invalid color\n");
	*color = rgb_to_hex(r, g, b);
}

void	set_ti(t_img *texture, const char *line, t_params *p)
{
	int		height;
	int		widht;
	char	*l;

	height = TEXHEIGHT;
	widht = TEXWIDHT;
	l = (char *)line;
	while (!is_space(*line))
		line++;
	while (is_space(*line))
		line++;
	texture->img = mlx_xpm_file_to_image(p->w.mlx, (char *)line, &widht,
			&height);
	texture->effective_height = height;
	texture->effective_widht = widht;
	if (!texture->img)
	{
		free(l);
		error(p, "coudn't read image\n");
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	if (!texture->addr)
		map_error(*p, 1, l);
}

void	set_identifier_handler(t_type_def type, char *line, t_params *p)
{
	if (type == NO && !p->no_texture.img)
		set_ti(&p->no_texture, line, p);
	else if (type == WE && !p->ea_texture.img)
		set_ti(&p->ea_texture, line, p);
	else if (type == EA && !p->we_texture.img)
		set_ti(&p->we_texture, line, p);
	else if (type == SO && !p->so_texture.img)
		set_ti(&p->so_texture, line, p);
	else if (type == F && !p->f_color)
		set_color(&p->f_color, line, p);
	else if (type == C && !p->c_color)
		set_color(&p->c_color, line, p);
	else
	{
		free(line);
		error(p, "incorrect identifier\n");
	}
}
