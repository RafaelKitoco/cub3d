/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:12:04 by rpambo            #+#    #+#             */
/*   Updated: 2024/11/20 10:15:12 by rpambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <time.h>
# include <mlx.h>
# include <mlx_int.h>
# include "keys.h"
# include "libft.h"

# define screenWidth 1920
# define screenHeight 1080

typedef struct s_map
{
	int **worldMap;
	int width;
	int height;
}	t_map;

typedef struct s_data
{
    void            *img;
    char            *addr;
    int             bits_per_pixel;
    int             line_length;
    int             endian;
}		t_data;

typedef struct s_player
{
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
    double moveSpeed;
    double rotSpeed;
}	t_player;

typedef struct s_vars
{
    void            *mlx;
    void            *win;
    t_data          img;
    int             x;
    int             y;
    t_player        player;
    t_map           map;
    char            *no_texture;
    char            *so_texture;
    char            *we_texture;
    char            *ea_texture;
    int             floor_color[3];
    int             ceiling_color[3];
}		t_vars;

typedef struct s_draw_params
{
    int	x;
    int	drawStart;
    int	drawEnd;
    int	color;
    double	perpwalldist;
    t_vars *vars;
}	t_draw_params;

void	parse_config(char *path, t_vars *vars);
void	print_texture_paths(t_vars *vars);
void	print_colors(t_vars *vars);
void	print_map(t_vars *vars);
int		keypress(int keycode, t_vars *vars);
int		keyrelease(int keycode, t_vars *vars);
int		destroy(int keycode, t_vars *vars);
int		motion(int button, int x, int y, t_vars *vars);
char	*ft_strdup(const char *s1);
char	*ft_itoa(int n);
void	update_player_position(t_vars *vars, int key_pressed);
void	move_player(t_vars *vars, double moveSpeed);
void	rotate_player(t_vars *vars, double rotSpeed);
void	display_debug_info(t_vars *vars, int key_pressed);
void	draw_line(t_draw_params params);
void	draw_frame(t_vars *vars);
void	calculateRay(int x, t_vars *vars, double *perpWallDist, int *color);
t_vars	*root_init(t_vars *vars);
void	calculate_fps(t_vars *vars);

#endif
