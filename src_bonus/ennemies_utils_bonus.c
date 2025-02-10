/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemies_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 06:28:43 by pledieu           #+#    #+#             */
/*   Updated: 2025/02/10 11:23:15 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

/**
 * @brief Determines the new position
 * for an enemy based on the player's position.
 * 
 * This function calculates the new position
 * of an enemy based on the player's position.
 * It compares the horizontal and vertical distance
 * between the player and the enemy to decide whether the enemy
 * should move towards the player along the x-axis or y-axis.
 * The function checks if the move is valid
 * (ensuring the new position is not a wall) and updates the
 * `new_x` and `new_y` variables with the enemy's calculated new position.
 * 
 * @param game Pointer to the game structure.
 * @param enemy Pointer to the enemy structure.
 * @param new_x Pointer to the x-coordinate of the enemy's new position.
 * @param new_y Pointer to the y-coordinate of the enemy's new position.
 */
void	determine_new_position(t_game *game, t_enemy *enemy,
	int *new_x, int *new_y)
{
	if (abs(game->player_x - enemy->x) > abs(game->player_y - enemy->y))
	{
		if (game->player_x > enemy->x && enemy->x + 1 < game->map_width
			&& game->map[enemy->y][enemy->x + 1] != '1')
			(*new_x)++;
		else if (game->player_x < enemy->x && enemy->x - 1 >= 0
			&& game->map[enemy->y][enemy->x - 1] != '1')
			(*new_x)--;
	}
	else
	{
		if (game->player_y > enemy->y && enemy->y + 1 < game->map_height
			&& game->map[enemy->y + 1][enemy->x] != '1')
			(*new_y)++;
		else if (game->player_y < enemy->y && enemy->y - 1 >= 0
			&& game->map[enemy->y - 1][enemy->x] != '1')
			(*new_y)--;
	}
}
