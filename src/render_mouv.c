/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mouv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:33:48 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/28 10:57:35 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int key_press_wrapper(int keycode, void *param) {
    return handle_movement(keycode, param);
}

int handle_movement(int keycode, void *param) {
    t_game *game = (t_game *)param;
    int new_x = game->player_x;
    int new_y = game->player_y;

    // Vérifier quelle touche est pressée
    if (keycode == 65307) { // ESC
        destroy_textures(game);
        exit(0);
    } else if (keycode == 'w' || keycode == 'W') // Haut
        new_y--;
    else if (keycode == 's' || keycode == 'S') // Bas
        new_y++;
    else if (keycode == 'a' || keycode == 'A') // Gauche
        new_x--;
    else if (keycode == 'd' || keycode == 'D') // Droite
        new_x++;

    // Vérifier que le joueur ne sort pas des limites de la map
    if (new_x < 0 || new_x >= game->map_width || new_y < 0 || new_y >= game->map_height) {
        printf("⛔ DEBUG: Mouvement hors limites !\n");
        return (0);
    }

    // Vérifier que le joueur ne se déplace pas sur un mur
    if (game->map[new_y][new_x] == '1') {
        printf("⛔ DEBUG: Collision avec un mur !\n");
        return (0);
    }

    // Vérifier si c'est un collectible
    if (game->map[new_y][new_x] == 'C') {
        printf("🍎 DEBUG: Collectible ramassé !\n");
        game->map[new_y][new_x] = '0'; // Retirer le collectible
    }

    // Mettre à jour la position du joueur
    game->map[game->player_y][game->player_x] = '0'; // L'ancienne position devient du sol
    game->map[new_y][new_x] = 'P'; // Le joueur prend sa nouvelle position

    game->player_x = new_x;
    game->player_y = new_y;
    game->moves++;

    printf("✅ DEBUG: Joueur déplacé à (%d, %d), Mouvements: %d\n", game->player_x, game->player_y, game->moves);

    // Mettre à jour l'affichage
    render_map(game);

    return (0);
}

