/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:50:16 by rpambo            #+#    #+#             */
/*   Updated: 2024/11/20 09:54:56 by rpambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

int	keypress(int keycode, t_vars *vars)
{
	if (keycode == W)
		update_player_position(vars, keycode);
	else if (keycode == S)
		update_player_position(vars, keycode);
	else if (keycode == A)
		update_player_position(vars, keycode);
	else if (keycode == D)
		update_player_position(vars, keycode);
	else if (keycode == LEFT)
		update_player_position(vars, keycode);
	else if (keycode == RIGHT)
		update_player_position(vars, keycode);
	else if (keycode == UP)
		update_player_position(vars, keycode);
	else if (keycode == DOWN)
		update_player_position(vars, keycode);
	else if (keycode == ESC)
		exit(0);
	return (0);
}

int	keyrelease(int keycode, t_vars *vars)
{
	(void)vars;
	if (keycode)
		printf("[%d] Key released.\n", keycode);
	return (0);
}

int	destroy(int keycode, t_vars *vars)
{
	(void)keycode;
	if (vars->mlx && vars->win)
	{
		mlx_clear_window(vars->mlx, vars->win);
		mlx_destroy_window(vars->mlx, vars->win);
		printf("Window destroyed.\n");
	}
	else
	{
		printf("Error: Attempted to destroy NULL mlx or win pointer.\n");
	}
	return (0);
}

int	motion(int keycode, int x, int y, t_vars *vars)
{
	(void)vars;
	printf("Keycode=%d | X=%d | Y=%d\n", keycode, x, y);
	return (0);
}
