/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:32:06 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/30 11:18:01 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/**
 * @brief Counts occurrences of 'P', 'E', and 'C' in the map.
 * 
 * @param game The game structure.
 * @param pos The current position in the map.
 * @param counts Structure tracking counts of player, exit, and collectibles.
 */
void	count_elements(t_game *game, t_position pos, t_counts *counts)
{
	char	tile;

	tile = game->map[pos.y][pos.x];
	if (tile == 'P')
		counts->player++;
	if (tile == 'E')
		counts->exit++;
	if (tile == 'C')
		counts->collectible++;
}

/**
 * @brief Validates characters in the map and updates count.
 * 
 * @param game The game structure.
 * @param pos The current position in the map.
 * @param counts Structure tracking counts of player, exit, and collectibles.
 */
void	validate_character(t_game *game, t_position pos, t_counts *counts)
{
	char	tile;

	tile = game->map[pos.y][pos.x];
	if (tile != '1' && tile != '0' && tile != 'P'
		&& tile != 'C' && tile != 'E' && tile != 'M')
	{
		ft_printf("Invalid character: '%c' (ASCII: %d) at line %d, col %d\n",
			tile, tile, pos.y, pos.x);
		error_exit("Error: Invalid character in the map!");
	}
	count_elements(game, pos, counts);
}

/**
 * @brief Checks if the map is rectangular.
 * 
 * @param game The game structure.
 */
void	validate_dimensions(t_game *game)
{
	int	i;
	int	line_length;

	i = 0;
	while (i < game->map_height)
	{
		if (!game->map[i])
		{
			ft_printf("Error\n: Line %d is NULL!\n", i);
			error_exit("Error\n: Invalid memory access!");
		}
		line_length = ft_strlen(game->map[i]);
		ft_printf("✅Validation - Line %d : Length %d (expected: %d) [%s]\n",
			i, line_length, game->map_width, game->map[i]);
		if (line_length != game->map_width)
		{
			ft_printf("Error\n: Line %d has incorrect length\n", i);
			error_exit("Error\n: The map is not rectangular!");
		}
		i++;
	}
}

/**
 * @brief Checks if the map has exactly one 'P', one 'E', and at least one 'C'.
 * 
 * @param counts Structure tracking counts of player, exit, and collectibles.
 */
void	validate_counts(t_counts counts)
{
	if (counts.player != 1)
	{
		ft_printf("Error\n: Must have exactly one 'P', found: %d\n",
			counts.player);
		error_exit("Error\n: Incorrect number of players!");
	}
	if (counts.exit != 1)
	{
		ft_printf("Error\n: Must have exactly one exit 'E', found: %d\n",
			counts.exit);
		error_exit("Error\n: Incorrect number of exits!");
	}
	if (counts.collectible < 1)
	{
		ft_printf("Error\n: Must have at least one collectible, found: %d\n",
			counts.collectible);
		error_exit("Error\n: No collectibles found!");
	}
}

/**
 * @brief Validates the map (walls, dimensions, characters, required elements).
 * 
 * @param game The game structure.
 */
void	validate_map(t_game *game)
{
	int			i;
	int			j;
	t_counts	counts;
	t_position	pos;

	counts.player = 0;
	counts.exit = 0;
	counts.collectible = 0;
	check_map_walls(game);
	validate_dimensions(game);
	i = -1;
	while (++i < game->map_height)
	{
		j = -1;
		while (++j < game->map_width)
		{
			pos.x = j;
			pos.y = i;
			validate_character(game, pos, &counts);
		}
	}
	validate_counts(counts);
	check_valid_path(game);
}
