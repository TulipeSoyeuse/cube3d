/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:45:46 by romain            #+#    #+#             */
/*   Updated: 2024/04/20 19:31:32 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_dir(t_params *p, char c)
{
	if (c == 'N')
	{
		p->p_dir.x = 0;
		p->p_dir.y = 1;
	}
	else if (c == 'S')
	{
		p->p_dir.x = 0;
		p->p_dir.y = -1;
	}
	else if (c == 'E')
	{
		p->p_dir.x = -1;
		p->p_dir.y = 0;
	}
	else if (c == 'W')
	{
		p->p_dir.x = 1;
		p->p_dir.y = 0;
	}
	else
		return (0);
	printf("dir: %f %f\n", p->p_dir.x, p->p_dir.y);
	return (1);
}

void	set_player_position(t_params *p)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	printf("setting player pos\n");
	while (p->map[i])
	{
		line = p->map[i];
		j = 0;
		while (line[j])
		{
			if (set_dir(p, line[j]))
			{
				p->p_pos.x = i;
				p->p_pos.y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	run(t_params *p)
{
	p->w.cur_img = get_new_image(p);
	p->w.cache_img = get_new_image(p);
	calc_image(p, p->w.cur_img);
	mlx_put_image_to_window(p->w.mlx, p->w.mlx_win, p->w.cur_img.img, 0, 0);
	loop(p);
}

t_img	get_new_image(t_params *p)
{
	t_img	image;

	image.img = mlx_new_image(p->w.mlx, SHEIGHT, SWIDTH);
	if (!image.img)
		cube_exit(p);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
			&image.line_length, &image.endian);
	if (!image.addr)
		error(p);
	return (image);
}

// void	calc_image(t_params *p, t_img img)
// {
// 	int				x;
// 	t_calc_values	cv;
// 	int				lineHeight;
// 	double			perpWallDist;
// 	int				drawStart;
// 	int				drawEnd;

// 	x = -1;
// 	reset_img_color(img);
// 	while (x++ < SWIDTH)
// 	{
// 		cv.deltaDist = dist(p, 2 * x / (double)SWIDTH - 1);
// 		printf("deltaDist: %f %f\n", cv.deltaDist.x, cv.deltaDist.y);
// 		calc_side_dist(p, &cv);
// 		cv.hit = False;
// 		while (cv.hit == False)
// 			is_hit(p, &cv);
// 		perpWallDist = get_perpwalldist(cv);
// 		lineHeight = (int)(SHEIGHT / perpWallDist);
// 		drawStart = -lineHeight / 2 + SHEIGHT / 2;
// 		if (drawStart < 0)
// 			drawStart = 0;
// 		drawEnd = lineHeight / 2 + SHEIGHT / 2;
// 		if (drawEnd >= SHEIGHT)
// 			drawEnd = SHEIGHT - 1;
// 		draw_ver_line(x, drawStart, drawEnd, img);
// 	}
// }

void	calc_image(t_params *p, t_img img)
{
	double	planeX;
	double	planeY;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;

	planeX = 0;
	double posX = 3, posY = 3; // x and y start position
	double dirX = 1, dirY = 0; // initial direction vector
	planeX = 0;
	planeY = 0.66;
	// the 2d raycaster version of camera plane
	for (int x = 0; x < SWIDTH; x++)
	{
		// calculate ray position and direction
		cameraX = 2 * x / (double)SWIDTH - 1;
		// x-coordinate in camera space
		rayDirX = dirX + planeX * cameraX;
		rayDirY = dirY + planeY * cameraX;
		// which box of the map we're in
		mapX = (int)posX;
		mapY = (int)posY;
		deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		// what direction to step in x or y-direction (either +1 or -1)
		int hit = 0; // was there a wall hit?
		int side;    // was a NS or a EW wall hit?
		// calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		// perform DDA
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// Check if ray has hit a wall
			if (p->map[mapX][mapY] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		// Calculate height of line to draw on screen
		lineHeight = (int)(SHEIGHT / perpWallDist);
		// calculate lowest and highest pixel to fill in current stripe
		drawStart = -lineHeight / 2 + SHEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + SHEIGHT / 2;
		if (drawEnd >= SHEIGHT)
			drawEnd = SHEIGHT - 1;
		draw_ver_line(x, drawStart, drawEnd, img);
	}
}
