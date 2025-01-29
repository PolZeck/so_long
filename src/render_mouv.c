/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mouv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:33:48 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/29 10:00:51 by pledieu          ###   ########lyon.fr   */
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
	int moved = 0; // Indicateur pour vérifier si on a bougé


    // Vérifier quelle touche est pressée
    if (keycode == 65307) { // Échap pour quitter proprement
        destroy_textures(game);
        exit(0);
    }

    // Détection des touches de mouvement
    if (keycode == 'w' || keycode == 'W' || keycode == 65362) { // Haut
        new_y--;
        moved = 1;
    } else if (keycode == 's' || keycode == 'S' || keycode == 65364) { // Bas
        new_y++;
        moved = 1;
    } else if (keycode == 'a' || keycode == 'A' || keycode == 65361) { // Gauche
        new_x--;
        moved = 1;
    } else if (keycode == 'd' || keycode == 'D' || keycode == 65363) { // Droite
        new_x++;
        moved = 1;
    }

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

    if (game->map[new_y][new_x] == 'E') {
    if (count_collectibles(game) > 0) {
        printf("⛔ Il reste encore des collectibles ! (%d restants)\n", count_collectibles(game));
        return (0);
    }
		printf("🎉 Victoire ! Vous avez collecté tous les objets et atteint la sortie en %d déplacements !\n", (game->moves + 1));
		destroy_textures(game);
		free_map(game);
		exit(0);
	}
    if (game->map[new_y][new_x] == 'C') {
        printf("🍎 DEBUG: Collectible ramassé !\n");
        game->map[new_y][new_x] = '0'; // Retirer le collectible
    }
    game->map[game->player_y][game->player_x] = '0'; // L'ancienne position devient du sol
    game->map[new_y][new_x] = 'P'; // Le joueur prend sa nouvelle position

    game->player_x = new_x;
    game->player_y = new_y;
    if (moved)
	{
		game->moves++;
		// write(1,"\033[H\033[J", 6);
	    ft_printf("\033[H\033[JJoueur déplacé à (%d, %d), Mouvements: %d\n", game->player_x, game->player_y, game->moves);
	}
    render_map(game);

    return (0);
}
