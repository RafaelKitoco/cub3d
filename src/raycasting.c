/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:55:36 by rpambo            #+#    #+#             */
/*   Updated: 2024/11/08 15:56:47 by rpambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

// Função para calcular a direção do raio e os passos
void calculateRayDirectionAndStep(double cameraX, t_vars *vars, double *rayDirX, double *rayDirY, int *stepX, int *stepY) {
    *rayDirX = vars->player.dirX + vars->player.planeX * cameraX;
    *rayDirY = vars->player.dirY + vars->player.planeY * cameraX;

    if (*rayDirX < 0) {
        *stepX = -1;
    } else {
        *stepX = 1;
    }

    if (*rayDirY < 0) {
        *stepY = -1;
    } else {
        *stepY = 1;
    }
}

void calculateSideDistances(double rayDirX, double rayDirY, double posX, double posY, int mapX, int mapY, double *sideDistX, double *sideDistY) {
    double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
    double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

    if (rayDirX < 0) {
        *sideDistX = (posX - mapX) * deltaDistX;
    } else {
        *sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }

    if (rayDirY < 0) {
        *sideDistY = (posY - mapY) * deltaDistY;
    } else {
        *sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }
}

int performDDAAlgorithm(int *mapX, int *mapY, int stepX, int stepY, double *sideDistX, double *sideDistY, double deltaDistX, double deltaDistY, t_vars *vars) {
    int hit = 0;
    int side = 0;

    while (hit == 0) {
        if (*sideDistX < *sideDistY) {
            *sideDistX += deltaDistX;
            *mapX += stepX;
            side = 0;
        } else {
            *sideDistY += deltaDistY;
            *mapY += stepY;
            side = 1;
        }

        if (vars->map.worldMap[*mapX][*mapY] > 0) {
            hit = 1;
        }
    }

    return side;
}

void calculatePerpWallDist(int side, double sideDistX, double sideDistY, double deltaDistX, double deltaDistY, double *perpWallDist) {
    if (side == 0) {
        *perpWallDist = (sideDistX - deltaDistX);
    } else {
        *perpWallDist = (sideDistY - deltaDistY);
    }
}

void setWallColor(int mapX, int mapY, int side, t_vars *vars, int *color) {
    int mapValue = vars->map.worldMap[mapX][mapY];
    int colors[] = {0xFFFF00, 0xFF0000, 0x00FF00, 0x0000FF, 0xFFFFFF};  // Cores das paredes

    if (mapValue < 0 || mapValue > 4) {
        mapValue = 0;
    }

    *color = colors[mapValue];

    if (side == 1) {
        *color = *color / 2;
    }
}

void calculateRay(int x, t_vars *vars, double *perpWallDist, int *color) {
    double cameraX = 2 * x / (double)(screenWidth) - 1;
    double rayDirX, rayDirY;
    int stepX, stepY;
    int mapX = (int)vars->player.posX;
    int mapY = (int)vars->player.posY;
    double sideDistX, sideDistY;

    calculateRayDirectionAndStep(cameraX, vars, &rayDirX, &rayDirY, &stepX, &stepY);

    double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
    double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

    calculateSideDistances(rayDirX, rayDirY, vars->player.posX, vars->player.posY, mapX, mapY, &sideDistX, &sideDistY);
    int side = performDDAAlgorithm(&mapX, &mapY, stepX, stepY, &sideDistX, &sideDistY, deltaDistX, deltaDistY, vars);
    calculatePerpWallDist(side, sideDistX, sideDistY, deltaDistX, deltaDistY, perpWallDist);
    setWallColor(mapX, mapY, side, vars, color);
}
