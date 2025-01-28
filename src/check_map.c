/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:32:06 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/28 13:50:30 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void validate_map(t_game *game) 
{
    int i, j;
	check_map_walls(game); // ✅ Vérifie que la carte est bien entourée de murs


    printf("✅ DEBUG: La carte est jouable !\n");

    if (!game->map) {
        error_exit("Erreur : game->map est NULL !");
    }

    for (i = 0; i < game->map_height; i++) {
        if (!game->map[i]) {
            ft_printf("Erreur : Ligne %d est NULL !\n", i);
            error_exit("Erreur : Accès mémoire invalide !");
        }

        int line_length = ft_strlen(game->map[i]); // Longueur réelle SANS '\n'

        ft_printf("✅ DEBUG: Validation - Ligne %d : Longueur %d (attendue: %d) [%s]\n",
               i, line_length, game->map_width, game->map[i]);

        if (line_length != game->map_width) {
            ft_printf("Erreur : Ligne %d a une longueur différente (%d au lieu de %d)\n",
                   i, line_length, game->map_width);
            error_exit("Erreur : La carte n'est pas rectangulaire !");
        }

        for (j = 0; j < line_length; j++) {
            if (game->map[i][j] != '1' && game->map[i][j] != '0' &&
                game->map[i][j] != 'P' && game->map[i][j] != 'C' &&
                game->map[i][j] != 'E') {
                ft_printf("Caractère invalide détecté : '%c' (Code ASCII: %d) à la ligne %d, colonne %d\n",
                       game->map[i][j], game->map[i][j], i, j);
                error_exit("Erreur : Caractère invalide dans la carte !");
            }
        }
    }
	
}

void check_map_walls(t_game *game) {
    // Vérifier la première et la dernière ligne
    for (int x = 0; x < game->map_width; x++) {
        if (game->map[0][x] != '1' || game->map[game->map_height - 1][x] != '1') {
            printf("Error\n");
            exit(1);
        }
    }

    // Vérifier la première et la dernière colonne de chaque ligne
    for (int y = 0; y < game->map_height; y++) {
        if (game->map[y][0] != '1' || game->map[y][game->map_width - 1] != '1') {
            printf("Error\n");
            exit(1);
        }
    }
}
