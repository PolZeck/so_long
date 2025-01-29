/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 08:46:03 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/29 09:08:13 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/**
 * @brief Checks if the map is completely surrounded by walls ('1').
 * 
 * This function ensures that:
 * - The first and last row are entirely made of '1'.
 * - The first and last column of each row are also '1'.
 * If any of these conditions fail, an error message is printed, 
 * and the program exits.
 * 
 * @param game The game structure containing the map.
 */
void	check_map_walls(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->map_width)
	{
		if (game->map[0][x] != '1' || game->map[game->map_height - 1][x] != '1')
		{
			ft_printf("Error\n");
			exit(1);
		}
		x++;
	}
	y = 0;
	while (y < game->map_height)
	{
		if (game->map[y][0] != '1' || game->map[y][game->map_width - 1] != '1')
		{
			ft_printf("Error\n");
			exit(1);
		}
		y++;
	}
}
