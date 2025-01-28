/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:51:34 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/28 10:45:45 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void load_map(const char *filename, t_game *game) {
    int fd;
    char *line;
    int i = 0;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_exit("Erreur : Impossible d'ouvrir la carte");

    game->map = malloc(sizeof(char *) * 100); // Allocation arbitraire
    if (!game->map)
        error_exit("Erreur : Allocation mémoire échouée");

    printf("✅ DEBUG: Allocation mémoire réussie pour game->map\n");

    while ((line = get_next_line(fd))) {
        if (line[0] == '\n') { // Ignore les lignes vides accidentelles
            free(line);
            continue;
        }

        printf("✅ DEBUG: Lecture de la ligne [%s]\n", line);

        // Supprimer le '\n' en fin de ligne pour uniformiser la map
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';

        if (i == 0)
            game->map_width = strlen(line);

        if (!line) {
            error_exit("Erreur : get_next_line() a retourné NULL !");
        }

        if ((int)strlen(line) != game->map_width) {
            printf("Erreur : Ligne %d a une longueur incorrecte [%s]\n", i, line);
            error_exit("Erreur : La carte n'est pas rectangulaire !");
        }

        game->map[i++] = line;
    }

    game->map[i] = NULL; // Fin de map
    game->map_height = i;
    close(fd);

    printf("✅ DEBUG: Carte chargée avec succès, hauteur: %d, largeur: %d\n", game->map_height, game->map_width);
}
