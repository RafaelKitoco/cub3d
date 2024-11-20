/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:56:35 by rpambo            #+#    #+#             */
/*   Updated: 2024/11/08 12:58:07 by rpambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

void update_player_position(t_vars *vars, int key_pressed) {
    mlx_clear_window(vars->mlx, vars->win);
    draw_frame(vars);

    if (key_pressed == 65307) // ESC key
        exit(0);

    // Right rotation (D key)
    if (key_pressed == 100) {
         rotate_player(vars, -vars->player.rotSpeed);
    }
    
    if (key_pressed == 65363) {
         rotate_player(vars, -vars->player.rotSpeed);
    }
    
    // Move backward (S key)
    if (key_pressed == 115) {
       move_player(vars, -vars->player.moveSpeed);
    }
    
    // Move backward (Down key)
    if (key_pressed == 65364) {
       move_player(vars, -vars->player.moveSpeed);
    }
    
    // Move forward (W key)
    if (key_pressed == 119) {
        move_player(vars, vars->player.moveSpeed);
    }
    
    // Move forward (Up key)
    if (key_pressed == 65362) {
        move_player(vars, vars->player.moveSpeed);
    }
    
    // Left rotation (A key)
    if (key_pressed == 97) {
        rotate_player(vars, vars->player.rotSpeed);
    }
    
    if (key_pressed == 65361) {
        rotate_player(vars, vars->player.rotSpeed);
    }
    
    display_debug_info(vars, key_pressed);

    calculate_fps(vars);
}
