/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:22:59 by rpambo            #+#    #+#             */
/*   Updated: 2024/11/20 10:11:13 by rpambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

void	move_player(t_vars *vars, double moveSpeed)
{
	if (vars->map.worldMap[(int)(vars->player.posX
			+ vars->player.dirX
			* moveSpeed)][(int)(vars->player.posY)] == 0)
	{
		vars->player.posX += vars->player.dirX * moveSpeed;
	}
	if (vars->map.worldMap[(int)(vars->player.posX)]
		[(int)(vars->player.posY + vars->player.dirY * moveSpeed)] == 0)
	{
		vars->player.posY += vars->player.dirY * moveSpeed;
	}
}

void	rotate_player(t_vars *vars, double rotSpeed)
{
	double	olddirx;
	double	oldplanex;

	olddirx = vars->player.dirX;
	vars->player.dirX = vars->player.dirX * cos(rotSpeed)
		- vars->player.dirY * sin(rotSpeed);
	vars->player.dirY = olddirx * sin(rotSpeed)
		+ vars->player.dirY * cos(rotSpeed);
	oldplanex = vars->player.planeX;
	vars->player.planeX = vars->player.planeX * cos(rotSpeed)
		- vars->player.planeY * sin(rotSpeed);
	vars->player.planeY = oldplanex * sin(rotSpeed)
		+ vars->player.planeY * cos(rotSpeed);
}
