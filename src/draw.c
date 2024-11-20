/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:53:07 by rpambo            #+#    #+#             */
/*   Updated: 2024/11/19 16:17:41 by rpambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear_image(t_data *img, int width, int height)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			my_mlx_pixel_put(img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	draw_line(t_draw_params params)
{
	int	y;

	y = params.drawStart;
	while (y <= params.drawEnd)
	{
		my_mlx_pixel_put(&params.vars->img, params.x, y, params.color);
		y++;
	}
}

void	calculate_and_draw_line(int x, t_vars *vars)
{
	int				lineheight;
	t_draw_params	params;

	calculateRay(x, vars, &params.perpwalldist, &params.color);
	lineheight = (int)(screenHeight / params.perpwalldist);
	params.drawStart = -lineheight / 2 + screenHeight / 2;
	if (params.drawStart < 0)
		params.drawStart = 0;
	params.drawEnd = lineheight / 2 + screenHeight / 2;
	if (params.drawEnd >= screenHeight)
		params.drawEnd = screenHeight - 1;
	params.x = x;
	params.vars = vars;
	draw_line(params);
}

void	draw_frame(t_vars *vars)
{
	int	x;

	clear_image(&vars->img, screenWidth, screenHeight);
	x = 0;
	while (x < screenWidth)
	{
		calculate_and_draw_line(x, vars);
		x++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}
