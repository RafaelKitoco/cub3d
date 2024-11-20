/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispaly_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:33:37 by rpambo            #+#    #+#             */
/*   Updated: 2024/11/19 13:19:17 by rpambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

void	display_pos(t_vars *vars, char *posx_str, char *posy_str)
{
	mlx_string_put(vars->mlx, vars->win, 10, 10, 0x00FF0000, "posX");
	mlx_string_put(vars->mlx, vars->win, 70, 10, 0x00FF0000, posx_str);
	mlx_string_put(vars->mlx, vars->win, 10, 30, 0x00FF0000, "posY");
	mlx_string_put(vars->mlx, vars->win, 70, 30, 0x00FF0000, posy_str);
	free(posx_str);
	free(posy_str);
}

void	display_key(t_vars *vars, char *key_code_str)
{
	mlx_string_put(vars->mlx, vars->win, 10, 50, 0x00FF0000, "keycode");
	mlx_string_put(vars->mlx, vars->win, 70, 50, 0x00FF0000, key_code_str);
	free(key_code_str);
}

void	display_dir(t_vars *vars, char *dirx_str, char *diry_str)
{
	mlx_string_put(vars->mlx, vars->win, 10, 90, 0x00FF0000, "rayDirX");
	mlx_string_put(vars->mlx, vars->win, 70, 90, 0x00FF0000, dirx_str);
	mlx_string_put(vars->mlx, vars->win, 10, 110, 0x00FF0000, "rayDirY");
	mlx_string_put(vars->mlx, vars->win, 70, 110, 0x00FF0000, diry_str);
	free(dirx_str);
	free(diry_str);
}

void	display_debug_info(t_vars *vars, int key_pressed)
{
	char	*posx_str;
	char	*posy_str;
	char	*key_code_str;
	char	*dirx_str;
	char	*diry_str;

	posx_str = ft_itoa((int)vars->player.posX);
	posy_str = ft_itoa((int)vars->player.posY);
	display_pos(vars, posx_str, posy_str);
	key_code_str = ft_itoa(key_pressed);
	display_key(vars, key_code_str);
	dirx_str = ft_itoa((int)vars->player.dirX);
	diry_str = ft_itoa((int)vars->player.dirY);
	display_dir(vars, dirx_str, diry_str);
	calculate_fps(vars);
}
