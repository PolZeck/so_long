/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:32:28 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/28 16:25:23 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void render_map(t_game *game) {
    int x, y;

    // Affichage des textures sur la carte
    for (y = 0; y < game->map_height; y++) {
        for (x = 0; x < game->map_width; x++) {
            if (game->map[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->img_wall, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[y][x] == '0')
                mlx_put_image_to_window(game->mlx, game->win, game->img_floor, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[y][x] == 'P')
                mlx_put_image_to_window(game->mlx, game->win, game->img_player, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[y][x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->img_collectible, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map[y][x] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->img_exit, x * TILE_SIZE, y * TILE_SIZE);
        }
    }

    // ✅ Ajout d'un fond derrière le texte (rectangle noir semi-transparent)
    int rect_x = 5, rect_y = 5, rect_width = 140, rect_height = 20;
    int color = 0x000000; // Noir
    for (int i = rect_y; i < rect_y + rect_height; i++) {
        for (int j = rect_x; j < rect_x + rect_width; j++) {
            mlx_pixel_put(game->mlx, game->win, j, i, color);
        }
    }

    // ✅ Affichage du compteur de mouvements avec une couleur bien visible
    char *move_count = ft_itoa(game->moves); // Convertir le compteur en string
    mlx_string_put(game->mlx, game->win, 15, 20, 0xFFD700, "Mouvements : "); // Jaune doré
    mlx_string_put(game->mlx, game->win, 120, 20, 0xFFFFFF, move_count); // Blanc
    free(move_count); // Libérer la mémoire

    printf("DEBUG: Nombre de mouvements affiché sur la fenêtre : %d\n", game->moves);
}


