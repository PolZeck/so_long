/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:51:47 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/28 13:15:33 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void init_game(t_game *game, char *map_file) {
    game->mlx = mlx_init();
    if (!game->mlx)
        error_exit("Erreur : Impossible d'initialiser MiniLibX");

    load_map(map_file, game);
    validate_map(game);
	set_player_position(game);


    game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE, game->map_height * TILE_SIZE, "so_long");
    if (!game->win)
        error_exit("Erreur : Impossible de créer la fenêtre");

    load_textures(game);
    render_map(game);
	mlx_key_hook(game->win, key_press_wrapper, game);
	mlx_hook(game->win, 17, 0, close_game, game); // ✅ Ferme proprement en cliquant sur la croix
    mlx_loop(game->mlx);
}

int close_game(t_game *game) {
    printf("👋 Fermeture du jeu !\n");
    destroy_textures(game);
    free_map(game);
    exit(0);
    return (0);
}
