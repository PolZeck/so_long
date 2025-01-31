/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemies_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 06:28:43 by pledieu           #+#    #+#             */
/*   Updated: 2025/01/31 07:38:09 by pledieu          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_enemies(t_game *game)
{
	t_enemy	*temp;

	while (game->enemies)
	{
		temp = game->enemies;
		game->enemies = game->enemies->next;
		free(temp);
	}
}

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
