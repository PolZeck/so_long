/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:33:11 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/28 11:02:54 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void load_textures(t_game *game) {
    int w, h;
    game->img_wall = mlx_xpm_file_to_image(game->mlx, "assets/wall.xpm", &w, &h);
    game->img_player = mlx_xpm_file_to_image(game->mlx, "assets/player.xpm", &w, &h);
    game->img_collectible = mlx_xpm_file_to_image(game->mlx, "assets/collectible.xpm", &w, &h);
    game->img_exit = mlx_xpm_file_to_image(game->mlx, "assets/exit.xpm", &w, &h);
    game->img_floor = mlx_xpm_file_to_image(game->mlx, "assets/floor.xpm", &w, &h);
    if (!game->img_wall || !game->img_player || !game->img_collectible || !game->img_exit || !game->img_floor)
        error_exit("Erreur : Impossible de charger une ou plusieurs textures.");
}

void set_player_position(t_game *game) {
    for (int y = 0; y < game->map_height; y++) {
        for (int x = 0; x < game->map_width; x++) {
            if (game->map[y][x] == 'P') {
                game->player_x = x;
                game->player_y = y;
                printf("✅ DEBUG: Joueur trouvé à -> X: %d, Y: %d\n", x, y);
                return;
            }
        }
    }
    error_exit("Erreur : Joueur non trouvé dans la carte !");
}
