/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:32:06 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/28 10:45:49 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
void validate_map(t_game *game) {
    int i, j;

    if (!game->map) {
        error_exit("Erreur : game->map est NULL !");
    }

    for (i = 0; i < game->map_height; i++) {
        if (!game->map[i]) {
            printf("Erreur : Ligne %d est NULL !\n", i);
            error_exit("Erreur : Accès mémoire invalide !");
        }

        int line_length = strlen(game->map[i]); // Longueur réelle SANS '\n'

        printf("✅ DEBUG: Validation - Ligne %d : Longueur %d (attendue: %d) [%s]\n",
               i, line_length, game->map_width, game->map[i]);

        if (line_length != game->map_width) {
            printf("Erreur : Ligne %d a une longueur différente (%d au lieu de %d)\n",
                   i, line_length, game->map_width);
            error_exit("Erreur : La carte n'est pas rectangulaire !");
        }

        for (j = 0; j < line_length; j++) {
            if (game->map[i][j] != '1' && game->map[i][j] != '0' &&
                game->map[i][j] != 'P' && game->map[i][j] != 'C' &&
                game->map[i][j] != 'E') {
                printf("Caractère invalide détecté : '%c' (Code ASCII: %d) à la ligne %d, colonne %d\n",
                       game->map[i][j], game->map[i][j], i, j);
                error_exit("Erreur : Caractère invalide dans la carte !");
            }
        }
    }
}
