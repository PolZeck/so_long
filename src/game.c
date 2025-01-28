/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:51:47 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/28 09:53:39 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void init_game(t_game *game, char *map_file) {
    game->mlx = mlx_init();
    if (!game->mlx)
        error_exit("Erreur : Impossible d'initialiser MiniLibX");

    load_map(map_file, game);
    validate_map(game);

    game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE, game->map_height * TILE_SIZE, "so_long");
    if (!game->win)
        error_exit("Erreur : Impossible de créer la fenêtre");

    load_textures(game);
    render_map(game);
	mlx_key_hook(game->win, key_press_wrapper, game);
    mlx_loop(game->mlx);
}

