/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdupeux <rdupeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:20:32 by romain            #+#    #+#             */
/*   Updated: 2024/12/06 16:09:15 by rdupeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cube_exit(t_params *p)
{
	cleanup(p);
	exit(EXIT_SUCCESS);
}

void	loop(t_params *p)
{
	display_params(p);
	mlx_key_hook(p->w.mlx_win, &key_hook, p);
	mlx_hook(p->w.mlx_win, 17, 0, &close_event, p);
	mlx_loop(p->w.mlx);
}
