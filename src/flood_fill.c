/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 08:15:05 by pledieu           #+#    #+#             */
/*   Updated: 2025/02/10 13:38:53 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/**
 * @brief Performs a flood-fill to check if the path is valid.
 * 
 * Recursively explores the map:
 * - Stops at walls ('1') or already visited cells ('V').
 * - Decreases collectible count when 'C' is found.
 * - Marks the exit as found if 'E' is reached.
 * - Marks visited cells with 'V' to avoid infinite recursion.
 * 
 * @param game The game structure containing relevant data.
 * @param map Copy of the game map.
 * @param y Vertical position.
 * @param x Horizontal position.
 */
void	flood_fill(char **map, int y, int x, t_counts *counts)
{
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	if (map[y][x] == 'C')
		counts->collectible--;
	if (map[y][x] == 'E')
	{
		counts->exit = 1;
		return ;
	}
	map[y][x] = 'V';
	flood_fill(map, y - 1, x, counts);
	flood_fill(map, y + 1, x, counts);
	flood_fill(map, y, x - 1, counts);
	flood_fill(map, y, x + 1, counts);
}

char	**copy_map(char **original, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		error_exit("Erreur : Échec d'allocation mémoire pour map_copy");
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(original[i]);
		if (!copy[i])
			error_exit("Erreur : Échec de copie de la map");
		i++;
	}
	copy[height] = NULL;
	return (copy);
}

void	get_player_and_collectibles(t_game *game, t_position *player,
		t_counts *counts)
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
				player->x = x;
				player->y = y;
			}
			else if (game->map[y][x] == 'C')
				counts->collectible++;
			x++;
		}
		y++;
	}
}

void	validate_flood_result(t_counts *counts, t_game *game, char **map_copy)
{
	if (counts->collectible > 0 || counts->exit == 0)
	{
		ft_printf("Erreur : Aucun chemin valide vers la sortie ");
		ft_printf("ou tous les collectibles ne sont pas accessibles !\n");
		free_map_copy(map_copy, game->map_height);
		free_invalid_map(game);
	}
	ft_printf("✅ DEBUG: Chemin vers la sortie validé avec succès !\n");
}

void	check_valid_path(t_game *game)
{
	char		**map_copy;
	t_position	player;
	t_counts	counts;

	map_copy = copy_map(game->map, game->map_height);
	player.x = -1;
	player.y = -1;
	counts.collectible = 0;
	counts.exit = 0;
	get_player_and_collectibles(game, &player, &counts);
	if (player.x == -1 || player.y == -1)
		error_exit("Erreur : Joueur introuvable !");
	flood_fill(map_copy, player.y, player.x, &counts);
	validate_flood_result(&counts, game, map_copy);
	free_map_copy(map_copy, game->map_height);
}
