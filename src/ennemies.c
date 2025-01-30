/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemies.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:51:41 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/30 17:47:41 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Fonction pour libérer tous les ennemis
void free_enemies(t_game *game)
{
    t_enemy *temp;
    while (game->enemies)
    {
        temp = game->enemies;
        game->enemies = game->enemies->next;
        free(temp);
    }
}

void move_enemies(t_game *game)
{
    t_enemy *enemy = game->enemies;
    int new_x = 0, new_y = 0;

    while (enemy)
    {
        new_x = enemy->x;
        new_y = enemy->y;

        if (abs(game->player_x - enemy->x) > abs(game->player_y - enemy->y))
        {
            if (game->player_x > enemy->x && enemy->x + 1 < game->map_width &&
                game->map[enemy->y][enemy->x + 1] != '1')
                new_x++;  // Aller à droite
            else if (game->player_x < enemy->x && enemy->x - 1 >= 0 &&
                game->map[enemy->y][enemy->x - 1] != '1')
                new_x--;  // Aller à gauche
        }
        else
        {
            if (game->player_y > enemy->y && enemy->y + 1 < game->map_height &&
                game->map[enemy->y + 1][enemy->x] != '1')
                new_y++;  // Aller en bas
            else if (game->player_y < enemy->y && enemy->y - 1 >= 0 &&
                game->map[enemy->y - 1][enemy->x] != '1')
                new_y--;  // Aller en haut
        }

        // Vérifier si l'ennemi a attrapé le joueur
        if (new_x == game->player_x && new_y == game->player_y)
        {
            printf("💀 GAME OVER ! Un ennemi vous a attrapé !\n");
            destroy_textures(game);
            free_map(game);
            free_enemies(game);
            exit(1);
        }

        // Déplacer l'ennemi seulement s'il avance sur une case valide
        if (game->map[new_y][new_x] == '0' || game->map[new_y][new_x] == 'C')
        {
            // Si l'ennemi quitte une case contenant un collectible, on le remet
            if (enemy->under_enemy == 'C')
                game->map[enemy->y][enemy->x] = 'C';
            else
                game->map[enemy->y][enemy->x] = '0';  // Sinon, sol par défaut

            // Mettre à jour la position et stocker la nouvelle case sous l'ennemi
            if (game->map[new_y][new_x] == 'C')
                enemy->under_enemy = 'C';
            else
                enemy->under_enemy = '0';

            enemy->x = new_x;
            enemy->y = new_y;

            // Placer l'ennemi sur la nouvelle case
            game->map[new_y][new_x] = 'M';
        }

        enemy = enemy->next;  // Passer à l'ennemi suivant
    }
}




// Fonction pour ajouter un ennemi à la liste chaînée
void add_enemy(t_game *game, int x, int y)
{
    t_enemy *new_enemy = malloc(sizeof(t_enemy));
    if (!new_enemy)
        error_exit("Erreur : Allocation mémoire pour un ennemi");

    new_enemy->x = x;
    new_enemy->y = y;

    // Vérification manuelle pour stocker la bonne valeur sous l'ennemi
    if (game->map[y][x] == 'C')
        new_enemy->under_enemy = 'C';
    else
        new_enemy->under_enemy = '0';

    new_enemy->next = game->enemies;
    game->enemies = new_enemy;
}




// Fonction qui parcourt la map et place les ennemis en mémoire
void set_enemies(t_game *game)
{
    int x, y;

    y = 0;
    while (y < game->map_height)
    {
        x = 0;
        while (x < game->map_width)
        {
            if (game->map[y][x] == 'M') // 'M' représente un ennemi sur la carte
                {
					    printf("M détecté dans la map à (x=%d, y=%d)\n", x, y);
						add_enemy(game, x, y);
				}
			x++;
        }
        y++;
    }
}
