/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:32:06 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/29 07:41:26 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void validate_map(t_game *game) 
{
    int i, j;
    int player_count = 0; // ✅ Nombre de 'P' trouvés
    int exit_count = 0;   // ✅ Nombre de 'E' trouvés
    int collectible_count = 0; // ✅ Nombre de 'C' trouvés

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
            char tile = game->map[i][j];

            // ✅ Vérifie que chaque case contient un caractère valide
            if (tile != '1' && tile != '0' && tile != 'P' && tile != 'C' && tile != 'E') {
                ft_printf("Caractère invalide détecté : '%c' (Code ASCII: %d) à la ligne %d, colonne %d\n",
                       tile, tile, i, j);
                error_exit("Erreur : Caractère invalide dans la carte !");
            }

            // ✅ Compte le nombre de 'P' (joueur)
            if (tile == 'P')
                player_count++;

            // ✅ Compte le nombre de 'E' (sortie)
            if (tile == 'E')
                exit_count++;

            // ✅ Compte le nombre de 'C' (collectibles)
            if (tile == 'C')
                collectible_count++;
        }
    }

    // ✅ Vérification du nombre de 'P' (doit être exactement 1)
    if (player_count != 1) {
        ft_printf("Erreur : Il doit y avoir exactement un seul 'P', trouvé : %d\n", player_count);
        error_exit("Erreur : Nombre de joueurs incorrect !");
    }

    // ✅ Vérification du nombre de 'E' (doit être exactement 1)
    if (exit_count != 1) {
        ft_printf("Erreur : Il doit y avoir exactement une seule sortie 'E', trouvé : %d\n", exit_count);
        error_exit("Erreur : Nombre de sorties incorrect !");
    }

    // ✅ Vérification qu'il y a au moins un 'C'
    if (collectible_count < 1) {
        ft_printf("Erreur : Il doit y avoir au moins un collectible 'C', trouvé : %d\n", collectible_count);
        error_exit("Erreur : Aucun collectible !");
    }
    printf("✅ DEBUG : La carte contient 1 joueur (P), 1 sortie (E) et %d collectible(s) (C).\n", collectible_count);
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
