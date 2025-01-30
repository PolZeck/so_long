/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:33:11 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/30 11:15:50 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	load_textures(t_game *game)
{
	int	h;
	int	w;

	game->img_wall
		= mlx_xpm_file_to_image(game->mlx, "assets/wall.xpm", &w, &h);
	game->img_player
		= mlx_xpm_file_to_image(game->mlx, "assets/player.xpm", &w, &h);
	game->img_collectible
		= mlx_xpm_file_to_image(game->mlx, "assets/collectible.xpm", &w, &h);
	game->img_exit
		= mlx_xpm_file_to_image(game->mlx, "assets/exit.xpm", &w, &h);
	game->img_floor
		= mlx_xpm_file_to_image(game->mlx, "assets/floor.xpm", &w, &h);
	game->img_enemy
		= mlx_xpm_file_to_image(game->mlx, "assets/enemy.xpm", &w, &h);
	if (!game->img_wall || !game->img_player || !game->img_collectible
		|| !game->img_exit || !game->img_floor || !game->img_enemy )
		error_exit("Erreur : Impossible de charger une ou plusieurs textures.");
}

void	set_player_position(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				ft_printf("✅ DEBUG: Joueur trouvé à -> X: %d, Y: %d\n", x, y);
				return ;
			}
			x++;
		}
		y++;
	}
	error_exit("Erreur : Joueur non trouvé dans la carte !");
}
#include "../includes/so_long.h"

// Fonction pour ajouter un ennemi à la liste chaînée
void add_enemy(t_game *game, int x, int y)
{
    t_enemy *new_enemy = malloc(sizeof(t_enemy));
    if (!new_enemy)
        error_exit("Erreur : Allocation mémoire pour un ennemi");

    new_enemy->x = x;
    new_enemy->y = y;
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
                add_enemy(game, x, y);
            x++;
        }
        y++;
    }
}

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
