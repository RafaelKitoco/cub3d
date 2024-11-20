/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:20:57 by rpambo            #+#    #+#             */
/*   Updated: 2024/11/19 12:33:18 by rpambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

void	calculate_fps(t_vars *vars)
{
	static int	fps = 0;
	static int	old_time = 0;
	static char	*fps_str;
	char		*tmp;	

	fps_str = NULL;
	if (fps_str == NULL)
		fps_str = ft_itoa(fps);
	if (fps_str == NULL)
		return ;
	fps++;
	if (old_time != 0 && old_time != time(NULL))
	{
		tmp = ft_itoa(fps);
		if (tmp == NULL)
			return ;
		free(fps_str);
		fps_str = tmp;
		fps = 0;
	}
	mlx_string_put(vars->mlx, vars->win, 10, 70, 0x00FF0000, "fps");
	mlx_string_put(vars->mlx, vars->win, 70, 70, 0x00FF0000, fps_str);
	old_time = time(NULL);
}

int	isber(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (file == 0)
		return (0);
	if (len < 5)
		return (0);
	if (ft_strcmp(file + len - 4, ".cub") != 0)
		return (0);
	return (1);
}

int	validation_args(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s (<name>.cub)\n", argv[0]);
		return (1);
	}
	if (isber(argv[1]) == 0)
	{
		printf("Invalid argument! (<name>.cub)");
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_vars	*vars;

	if (validation_args(argc, argv))
		return (1);
	vars = malloc(sizeof(t_vars));
	if (!vars)
	{
		perror("Failed to allocate memory for vars");
		return (1);
	}
	parse_config(argv[1], vars);
	vars = root_init(vars);
	if (!vars)
	{
		free(vars);
		return (1);
	}
	draw_frame(vars);
	mlx_hook(vars->win, 2, 1L << 0, keypress, vars);
	mlx_loop(vars->mlx);
	free(vars);
	return (0);
}
