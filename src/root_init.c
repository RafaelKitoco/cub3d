/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:06:15 by rpambo            #+#    #+#             */
/*   Updated: 2024/11/08 16:06:48 by rpambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

// Função para carregar uma textura usando MiniLibX
static void *load_texture(void *mlx, char *path) {
    int width, height;
    void *img = mlx_xpm_file_to_image(mlx, path, &width, &height);
    if (!img) {
        ft_printf("Error loading texture: %s\n", path);
        exit(1);
    }
    return img;
}

t_vars *root_init(t_vars *vars) {
    // Inicializa a janela do MiniLibX
    vars->mlx = mlx_init();
    if (!vars->mlx) {
        ft_printf("Error initializing MiniLibX\n");
        exit(1);  // Encerra o programa se o MiniLibX não for inicializado
    }

    vars->win = mlx_new_window(vars->mlx, screenWidth, screenHeight, "Raycaster");
    if (!vars->win) {
        ft_printf("Error creating window\n");
        exit(1);  // Encerra o programa se a janela não for criada
    }

    vars->img.img = mlx_new_image(vars->mlx, screenWidth, screenHeight);
    vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);    
   
    // Carregar texturas
    vars->no_texture = load_texture(vars->mlx, vars->no_texture);
    vars->so_texture = load_texture(vars->mlx, vars->so_texture);
    vars->we_texture = load_texture(vars->mlx, vars->we_texture);
    vars->ea_texture = load_texture(vars->mlx, vars->ea_texture);

    // Inicializa as variáveis do jogado
    //vars->player.planeX = 0;
    //vars->player.planeY = 0.66;
    vars->player.moveSpeed = 0.20;
    vars->player.rotSpeed = 0.05;

    return vars;
}
